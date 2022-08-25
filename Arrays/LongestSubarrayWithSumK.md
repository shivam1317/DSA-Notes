## problem

>Given an array containing **N** integers and an integer **K**., Your task is to find the length of the longest Sub-Array with the sum of the elements equal to the given value **K**.

## Example:

**Input :**
```
A[] = {10, 5, 2, 7, 1, 9}
K = 15
```
**Output :** 
```
4
```
**Explanation:**
```
The sub-array is {5, 2, 7, 1}.
```

## Approach:

--> So first of all if we think about `brute force method` then we have to run 2 for loops and then find sum for all subarrays and then find the subarrays with `K` sum and then take the longest value but clearly this code;'s time complexity will be `O(n^2)`.

There is one more approach which is `2 pointer approach with sliding window` but it will also not work here because this arrays can contain negative numbers also.

--> So now there is one more approach in which we will compute `prefix sum` of all element and store them in map. Let's see it in diagram.

```
For example our array is [5,2,7,1,9] and K is 10
Prefix sum array will be [5,7,14,15,24]
```

Now we know that there is only one subarray with sum `10` which is `[2,7,1]` but how we will find it's length and why prefix sum is useful here?

![](../GFG/Attachments/Pasted%20image%2020220818145209.png)

we will store key as prefixSum and value as index in our map.

So now for each element we will check if `PrefixSum - K` is present in our map or not and if it's present then we will have one subarray with sum `K` and we can get it's length by doing `i-mp[prefixSum-K]`.

![](../GFG/Attachments/Pasted%20image%2020220818145858.png)

## Edge case

--> If at any point prefixSum becomes `K` then we will also consider `i+1` as valid answer.

## Final code:

```cpp
int lenOfLongSubarr(int A[],  int N, int K) 
{ 
	unordered_map<int,int>mp;
	int ans = 0;
	// prefix Sum
	int currSum = 0;
	for(int i=0;i<N;i++){
		currSum += A[i];
		// Edge case
		if(currSum == K){
			ans = i+1;
		}
		// If currSum-K is present in map
		else if(mp.find(currSum - K) != mp.end()){
			ans = max(ans,i-mp[currSum-K]);
		}
		// If not present then add it's index as value in map
		if(mp.find(currSum) == mp.end()){
			mp[currSum] = i;
		}
	}
	return ans;
} 
```

#Array #SlidingWindow 

