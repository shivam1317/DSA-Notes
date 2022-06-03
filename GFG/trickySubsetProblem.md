## Problem:

>N children are made to stand in a queue. Each of them is given a number A[i]. The teacher writes a number S on a page and passes it to the first child. Each child must add all the numbers they see on the page along with their own number, write the sum on the paper and pass it to the next person.
In the end, the teacher must determine if X can be formed by adding some of the numbers from the series of numbers written on the paper.

## Example:

**Input:** 
```
S = 1, N = 4, X = 7
A = {1, 2, 4, 2}
```
**Output:** 
```
yes
```
**Explaination:** 
```
The final sequence of numbers on the paper is 1, 2, 5, 12, 22. Using 2 and 5 we can form 7.
```

## Approach:

--> Here we can see that the final array which is `1,2,5,12,22` is in increasing order so we can call this array `temp` and we will keep running while loop from end to 0 and we will deduct `temp[i]` from X and we will run this till X becomes 0 or i becomes 0. and if X becomes 0 then we can form X using characters of `temp` array so we will return `1` else we will return `0`

--> Now we can optimise this in one way like during making `temp` array we will check `If the element which is gonna add in temp array is greater than X` then we will break the loop because we don't need the values which are greater than `X`.

So final code will look like this:

## Code:

```cpp
int isPossible(long long S, long long N, long long X, long long A[])
    {
        long long prefix = S;
        long long limitIdx = -1;
		// If at starting S is greater than X then we can't make X
        if(S > X){
            return 0;
        }
        vector<long long>temp;
        temp.push_back(S);
        int i = 0;
        for(;i<N;i++){
            temp.push_back(prefix+A[i]);
            prefix += temp[i+1];
            if(temp[i+1] >= X){
                i++;
                break;
            }
        }
	// If last element of temp array is equal to X then we will return 1
        if(temp[i] == X){
            return 1;
        }
        while(i>=0 && X >= 0){
			// if temp[i] is smaller than X then only we will deduct it
            if(X >= temp[i]){
                X -= temp[i];
            }
            if(X == 0){
                return 1;
            }
            i--;
        }
        return 0;
    }
```