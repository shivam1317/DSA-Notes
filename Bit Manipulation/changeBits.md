## Problem:

>Given a number **N,** complete the following tasks,  
Task 1. Generate a new number from N by changing the zeroes in the binary representation of N to 1.  
Task  2. Find the difference between N and the newly generated number.

## Example:

**Input:** 
```
N= 8
```
**Output:** 
```
7 15
```
**Explanation:**
```
There are 3 zeroes in binary representation of 8. Changing them to 1 will give 15. Difference between these two is 7.
```

## Approach:

--> We know that any number which have all bits are `1` will be `(2^i)-1` for example `111 is 15 which is equal to (2^4)-1` so we will take one temp variable and keep adding `2` in it and when it becomes more than N then we will stop and answers to our 2 questions will be:

```
1. temp-1-N
2. temp-1
```

## Code:

```cpp
	vector<int> changeBits(int N) {
        int temp = 1;
        while(N>=temp){
            temp*=2;
        }
        temp--;
        return {temp-N,temp};
    }
```