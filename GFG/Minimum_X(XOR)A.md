## Problem:

>Given two integers **A** and **B**, the task is to find an integer **X** such that **(X XOR A)** is minimum possible and the count of set bit in **X** is equal to the count of set bits in **B**.

## Example:

**Input:** 
```
A = 3, B = 5
```
**Output:** 
```
3
```
**Explanation:**
```
Binary(A) = Binary(3) = 011
Binary(B) = Binary(5) = 101
The XOR will be minimum when x = 3
i.e. (3 XOR 3) = 0 and the number
of set bits in 3 is equal
to the number of set bits in 5.
```

## Approach:

--> In this question first we will find the number of `set bits` in A and B and then we will apply below 3 conditions:

==> we will call number of set bits in A as `aset` and number of set bits in B as `bset`

```
1. If aset is equal to bset then return a
2. If aset > bset then traverse A and make every set bit as unset (A-B) times.
3. If aset < bset then traverse A and make every unset bit as set (B-A) times.
```

--> But there will be some edge cases:

If we are in condition `2` and traversing A to make every set bit as unset then first we have to check that `if any bit is already unset then we will skip that bit and goto next bit without doing anything`.

If we are in condition `3` and traversing A to make every unset bit as set then first we have to check that `If any bit is already set then we will skip that bit and goto next bit`.

## Code:

```cpp
    // Function to check if given bit is set or not
    bool checkset(int n,int index){
        n = n & (1<<index);
        if(n == 0){
            return false;
        }
        return true;
    }
    // Function to count the number of set bits in number
    int countset(int n){
        int count = 0;
        while(n!=0){
        	n = n&(n-1);
        	count++;
        }
        return count;
    }
    int minVal(int a, int b) {
        int aset = countset(a);
        int bset = countset(b);
        if(aset == bset){
            return a;
        }else if(aset > bset){
            int temp = aset-bset;
            int i=0;
            while(temp){
				// Checking if it's already unset
                if(!checkset(a,i)){
                    i++;
                }else{
					// Unsetting the bit
                    int mask = 1<<i;
                    a = a&(~mask);
                    i++;
                    temp--;
                }
            }
            return a;
        }else{
            int temp = bset-aset;
            int i = 0;
            while(temp){
				// Checking if it's already set
                if(checkset(a,i)){
                    i++;
                }else{
					// Setting the bit
                    int mask = 1<<i;
                    a = a | mask;
                    i++;
                    temp--;
                }
            }
            return a;
        }
    }
```

