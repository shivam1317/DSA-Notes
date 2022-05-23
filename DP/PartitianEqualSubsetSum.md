## Problem:

>You are given an array 'ARR' of 'N' positive integers. Your task is to find if we can partition the given array into two subsets such that the sum of elements in both subsets is equal.

 
## Example:
```
For example, let’s say the given array is [2, 3, 3, 3, 4, 5], then the array can be partitioned as [2, 3, 5], and [3, 3, 4] with equal sum 10.
```

## Approach:

--> Here we have to divide the array in `exact 2 subsets` and we have to make their sum equal so if whole array sum is `s` then the both subsets will have `s/2` sum so `we just have to find one subarray with sum s/2` because if we find one subset with sum s/2 then other subset will automatically have sum s/2 and we will return `true`

## Code:

```cpp
bool subSetSum(vector<int>&arr,int n,int k){
    vector<bool>prev(k+1,false),curr(k+1,false);
    prev[0] = true;
    if(arr[0] <= k){
        prev[arr[0]] = true;
    }
    for(int i=1;i<n;i++){
        curr[0] = true;
        for(int target=1;target<=k;target++){
            int notTake = prev[target];
            int take = false;
            if(target >= arr[i]){
                take = prev[target-arr[i]];
            }
            curr[target] = notTake || take;
        }
        prev = curr;
    }
    return prev[k];
}

bool canPartition(vector<int> &arr, int n)
{
    int sum = 0;
	for(int i=0;i<n;i++){
        sum += arr[i];
    }
    if(sum % 2 != 0){
        return false;
    }
    return subSetSum(arr,n,sum/2);
}
```

