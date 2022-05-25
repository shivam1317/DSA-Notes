## Problem:

>You are given an array containing N non-negative integers. Your task is to partition this array into two subsets such that the absolute difference between subset sums is minimum.
 You just need to find the minimum absolute difference considering any valid division of the array elements.
 
==> Note:

```
1. Each element of the array should belong to exactly one of the subset.

2. Subsets need not be contiguous always. For example, for the array : {1,2,3}, some of the possible divisions are a) {1,2} and {3}  b) {1,3} and {2}.

3. Subset-sum is the sum of all the elements in that subset. 
```

## Example:
Input

```
arr[] = [2,3,3,5]
```

Output:

```
1
```

Explaination:

```
If we take s1 as [2,5] and s2 as [3,3] then their sum difference will be 
7-6
1
```

## Approach:

--> Now we can find possible sum values for `s1` using `subsetSum` problem in which we used the dp array. So from that dp array's last row we can find all possible sum for s1.

So min sum for `s1` will be `0` when it don't have any element and the maximum sum for `s1` will be `sum of all elements` when it contains all elements of the array.

so our matrix will be of size `N x Sum of all elements+1`

--> For example for arr `[2,2,3]` the dp matrix will look like this:

![](../GFG/Attachments/Pasted%20image%2020220523195538.png)

--> So now if we fill the last row for array `[2,2,3]` it will look like this:

The highlighted part is the last row which will show us all possible sums.

![](../GFG/Attachments/Pasted%20image%2020220523195839.png)

--> Now if we write all sum values for s1 and s2 it will look like this:

![](../GFG/Attachments/Pasted%20image%2020220523200103.png)

--> Now we just have to take the `absolute difference of them` and find the `minimum` difference.

But here we don't have to take them all. instead we can go till half way because we can see that the values are swapping in other half. 

![](../GFG/Attachments/Pasted%20image%2020220523200423.png)

--> So first we will make our `dp` array using subsetSum problem and after that we will traverse it's last row and then find the valid sums and find the minimum absolute sum.

## Code:

```cpp
int minSubsetSumDifference(vector<int>& arr, int n)
{
	int sum = 0;
    for(int i=0;i<n;i++){
        sum += arr[i];
    }
	// Our target will be the sum of all elements and we will make dp array using subsetSum problem algorithm.
    int k = sum;
    vector<vector<bool>>dp(n,vector<bool>(k+1,false));
    for(int i=0;i<n;i++){
        dp[i][0] = true;
    }
    if(arr[0] <= k){
        dp[0][arr[0]] = true;
    }
    for(int i=1;i<n;i++){
        for(int target=1;target<=k;target++){
            int notTake = dp[i-1][target];
            int take = false;
            if(target >= arr[i]){
                take = dp[i-1][target-arr[i]];
            }
            dp[i][target] = notTake || take;
        }
    }
	// it will store our ans
    int mini = 1e9;
	// Traversing last row of dp array till half path
    for(int i=0;i<=k/2;i++){
        if(dp[n-1][i]){
            int s1 = i;
            int s2 = sum-s1;
            mini = min(mini,abs(s2-s1));
        }
    }
    return mini;
}
```

## Complexity:

```
Time complexity: O(N) + O(Nxtarget) + O(target/2)
Space complexity: O(Nxtarget)
```

Note:

>you can also use the space optmised version of subsetProblem to optimise the space complexity to O(target)


