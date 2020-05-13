#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>




// Custom Functions
char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
      {
            return str;
      }


      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      
      return str;
}


void intal_swap(char *num1, char *num2)
{
	char *temp = num1;
	num1 = num2;
	num2 = temp;
}


// ----------------------------------------------------------------END OF COUSTOM FUNCTIONS--------------------------------------------------------------------

// Returns the sum of two intals.
char* intal_add(char* intal1, char* intal2)
{
	// Find the length of both the strings
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);

	bool isFirstBigger = false;

	// Declare empty ans array
	char *ans = (char*)malloc(sizeof(char)*(len2+1));
	if(len1 >= len2)
	{
		char *ans = (char*)malloc(sizeof(char)*(len1+1));
		isFirstBigger = true;
	}	
	

	// Reversing the strings
	strrev(intal1);
	strrev(intal2);

	// Declare index = 0 for ans array
	int ansIndex = 0;
	int carry = 0;
	// Add digit by digit
	if(isFirstBigger)
	{
		
		for(int i = 0; i < len2; i++)
		{
			// Find sum of digits
			int sum = (intal1[i] - '0') + (intal2[i] - '0') + carry;
				
			// Add the sum digit to ans
			ans[ansIndex] = sum%10 + '0';
			ansIndex++;

			// Calculate the carry
			carry = sum/10;
		}


		// Append all the remaining digits
		for (int i = len2; i < len1; ++i)
		{
			ans[ansIndex] = intal1[i];
			ansIndex++;
		}

		// Append the remaining carry over
		if(carry)
		{
			ans[ansIndex] = carry + '0';
		}
	}

	else
	{
		for(int i = 0; i < len1; i++)
		{
			// Find sum of digits
			int sum = (intal1[i] - '0') + (intal2[i] - '0') + carry;
				
			// Add the sum digit to ans
			ans[ansIndex] = sum%10 + '0';
			ansIndex++;

			// Calculate the carry
			carry = sum/10;
		}


		// Append all the remaining digits
		for (int i = len1; i < len2; ++i)
		{
			ans[ansIndex] = intal2[i];
			ansIndex++;
		}

		// Append the remaining carry over
		if(carry)
		{
			ans[ansIndex] = carry + '0';
		}

	}


	// Reverse the ans so as to get the LSD and MSD correctly
	strrev(ans);

	return ans;

	
}


// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(char* intal1, char* intal2)
{
	// Find the length of both the strings
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);


	// Return 1 if len of string 1 is greater
	if(len1 > len2)
	{
		return 1;
	} 

	// Return -1 if length of string 2 is greater
	else if(len2 > len1)
	{
		return -1;
	}

	// If the lengths are equal
	else
	{
		// Compare character by character
		for(int i = 0; i < len1; i++)
		{
			// If equal then continue comparison
			if( intal1[i] == intal2[i] )
			{
				continue;
			}

			// If first character is greater then return 1
			else if(intal1[i] > intal2[i])
			{
				return 1;
			}

			// If second character is greater than first return -1
			else
			{
				return -1;
			}
		}

		// If all characters are equal
		return 0;
	}

}

// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(char* intal1, char* intal2)
{
	// Compare the numbers and find out which one is bigger
	int cmpr = intal_compare(intal1, intal2);

	// Find the length of both the strings
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);


	// Reversing the strings
	strrev(intal1);
	strrev(intal2);

	char * ans = (char*)malloc(sizeof(char)*len1);

	if(cmpr<0)
	{
		char * ans = (char*)malloc(sizeof(char)*len2);
	}

	
	// finding the difference
	if(cmpr == 0)
	{
		char *duh = (char*)malloc(sizeof(char)*1);
		duh[0] = '0';
		return duh;
	}

	else if(cmpr == 1)
	{
		int carry = 0;

		int ansIndex = 0;
		for(int i = 0; i < len2; i++)
		{
			int sub = ((intal1[i]  - intal2[i]) - carry);

			if(sub < 0)
			{
				sub += 10;
				carry = 1;
			}

			else
			{
				carry = 0;
			}

			ans[ansIndex] = (char)(sub + '0');
			ansIndex++;
		}

		// Remaining digits
		for(int i = len2; i < len1; i++)
		{
			int sub = ((intal1[i] - '0') - carry);

			if(sub < 0)
			{
				sub += 10;
				carry = 1;
			}
			else
			{
				carry = 0;
			}

			ans[ansIndex] = (char)(sub + '0');
			ansIndex++;

		}

		strrev(ans);

		int startIndex = 0;
		int ansLen = strlen(ans);

		for (int i = 0; i < ansLen; i++)
		{
			if(ans[i] != '0')
			{
				startIndex = i;
				break;
			}	
		}

		char* retAns = (char*)malloc(sizeof(char)*(ansLen-startIndex));
		for(int i = startIndex; i < ansLen; i++)
		{
			retAns[i-startIndex] = ans[i];
		}
		free(ans);
		return retAns;		
	}

	else if(cmpr == -1)
	{
		return intal_diff(intal2, intal1);
	}


}


// Returns the product of two intals.
char* intal_multiply(char* intal1, char* intal2)
{
	// Find the length of both the strings
	int len1 = strlen(intal1);
	int len2 = strlen(intal2);

	// Length check
	if(len1 == 0 || len2 == 0)
	{
		return NULL;
	}

	// Declare the ans array
	char* ans = (char*)malloc(sizeof(char)*(len1+len2));

	// Indexes for digits in numbers
	int index_num1 = 0;
	int index_num2 = 0;

	int digitCounter = 0;


	// Multiplication loop
	for(int i = len1-1; i >= 0; i--)
	{
		int carry = 0; 
        int n1 = intal1[i] - '0'; 


        // Shifting position nafter every multiplication
        index_num2 = 0;

        // Pair multiplication
        for(int j = len2-1; j >= 0; j--)
        {
        	// get current digit of second number 
            int n2 = intal2[j] - '0';

            // multiply the digits and add the carry
            int sum = n1*n2 + ans[index_num1 + index_num2] + carry;

            carry = sum/10;

            // Append the ans
            ans[index_num1 + index_num2] = sum%10;
            digitCounter++;

            // Increment the index
            index_num2++;

        }


        // Store the carry over in next block
        if (carry > 0) 
        {
            ans[index_num1 + index_num2] += carry; 
        }
  
        // Shift position to the left after each multiplication of a digit in intal1. 
        index_num1++; 

	}

	// Ignoring leading zeros
	int idx = digitCounter - 1;

	while(idx >= 0 && ans[idx]==0)
	{
		idx--;
	}

	// If pdct is zero
	if (idx == -1)
	{
		char* retAns = (char*)malloc(sizeof(char));
		retAns[0] = '0';
    	return retAns; 
	} 


	int count = 0;
	char* retAns = (char*)malloc(sizeof(char)*(idx+1));
	while(idx >= count)
	{
		retAns[count++] = ans[idx-count]; 
	}

	return retAns;

}

// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
char* intal_mod(char* intal1, char* intal2)
{
	return NULL;
}

// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
char* intal_pow(char* intal1, char* intal2)
{
	return NULL;
}

// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n)
{
	if(n <= 1)
	{
		char *ans = (char*)malloc(sizeof(char));
		if(n == 0)
		{
			ans[0] = '0';
		}
		else if(n == 1)
		{
			ans[0] = '1';
		}

		return ans;
		
	}

	return intal_add( intal_fibonacci(n-1) , intal_fibonacci(n-2));

}

// Returns Greatest Common Devisor of intal1 and intal2.
// Let GCD be "0" if one of intal1 and intal2 is "0".
char* intal_gcd(char* intal1, char* intal2)
{
	char zero[1] = "0";

	if(intal_compare(intal1, zero) == 0)
	{
		return intal2;
	}

	if(intal_compare(intal2, zero) == 0)
	{
		return intal1;
	}

	int cmp = intal_compare(intal1, intal2);

	if(cmp == 0)
	{
		return intal1;
	}

	else if(cmp == 1)
	{
		return intal_gcd(intal_diff(intal1, intal2) , intal2);
	}

	else
	{
		return intal_gcd(intal1, intal_diff(intal2, intal1));	
	}


}

// Returns the factorial of n.
char* intal_factorial(unsigned int n)
{
	if(n == 1)
	{
		char *a = (char*)malloc(sizeof(char));
		a[0] = '1';
		return a;
	}

	char num[1000];
	// Make string outta integer
	sprintf(num, "%u", n);

	return intal_multiply(num,intal_factorial(n-1));
}

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the reurning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n.k).
char* intal_bincoeff(unsigned int n, unsigned int k)
{

	return NULL;
}

// Returns the offset of the largest intal in the array.
// 1 <= n <= 1000
int intal_max(char **arr, int n)
{
	// Declare offset as 0
	int offset = 0;

	for (int i = 0; i < n; i++)
	{
		if(intal_compare(arr[i], arr[offset]))
		{
			offset = i;
		}	
	}

	return offset;
}

// Returns the offset of the smallest intal in the array.
// 1 <= n <= 1000
int intal_min(char **arr, int n)
{
	// Declare offset as 0
	int offset = 0;

	for (int i = 0; i < n; i++)
	{
		if(intal_compare(arr[i], arr[offset]) == -1)
		{
			offset = i;
		}	
	}

	return offset;
}

// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, char* key)
{
	// Declare offset as 0
	int offset = -1;

	// Linear Search
	for (int i = 0; arr[i] != NULL; i++)
	{
		if(intal_compare(arr[i],key) == 0)
		{
			offset = i;
			break;
		}	
	}

	return offset;

	return 0;
}

// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
int intal_binsearch(char **arr, int n, char* key)
{
	// Declare offset as 0
	int offset = -1;

	int start = 0;
	int end = n-1;
	int mid;

	while(start <= end)
	{	
		// Find the middle index
		mid = (start+end)/2;
		
		// Compare the elements
		int cmp = intal_compare(arr[mid], key);
		
		if(cmp == 0)
		{
			offset = mid;
			break;
		}
		else if(cmp == 1)
		{
			end = mid-1;

		}
		else
		{
			start = mid+1;
		}
	}

	return offset;
}



//----------------------------------------------------------------------------------------------------------------

void heapify(char **arr, int n, int i)
{
	int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if(l < n && intal_compare(arr[l], arr[largest]) == 1)
        largest = l; 
  
    // If right child is larger than largest so far 
    if(r < n && intal_compare(arr[r], arr[largest]) == 1)
        largest = r; 
  
    // If largest is not root 
    if (largest != i)
    { 
        intal_swap(arr[i], arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    }
}

//--------------------------------------------------------------------------------------------------------------------


// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
void intal_sort(char **arr, int n)
{
	// Implementing HeapSort for O(nlog(n))

    for(int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i=n-1; i>0; i--) 
    { 
        // Move current root to end 
        intal_swap(arr[0], arr[i]); 
  
        heapify(arr, i, 0); 
    }

	return;
}

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
void coin_row_problem(char **arr, int n)
{
	return;
}





/*

TO DO List

1. Improve sub func, it doesnt work maybe
2. Ask if key is to be taken input or the key will be an argument
3. Test all functions

*/