## Problem:

>You are given an array ‘ARR’ of ‘N’ integers and a target number, ‘TARGET’. Your task is to build an expression out of an array by adding one of the symbols '+' and '-' before each integer in an array, and then by concatenating all the integers, you want to achieve a target. You have to return the number of ways the target can be achieved.

## Example:

```
You are given the array ‘ARR’ = [1, 1, 1, 1, 1], ‘TARGET’ = 3. The number of ways this target can be achieved is:
1. -1 + 1 + 1 + 1 + 1 = 3
2. +1 - 1 + 1 + 1 + 1 = 3
3. +1 + 1 - 1 + 1 + 1 = 3
4. +1 + 1 + 1 - 1 + 1 = 3
5. +1 + 1 + 1 + 1 - 1 = 3
These are the 5 ways to make. Hence the answer is 5.
```

## Approach:

--> We can do this question in 2 ways:

1. normal DP way where we will take 2 conditions: use `+` or use `-` and find all possible ways and return count of them
2. This question is very similar to `subset Partition problem` in which we divide our array in 2 partitions and then find the number of partitions with given sum. here also we can make 2 partitions for `numbers with + sign` and `numbers with - sign` and use the same algo to find all possible partitions which have difference equal to given sum.

--> So we will use 2nd way here!

## Code:

```cpp
int solve(int tar,vector<int>&arr){
    int n = arr.size();
    vector<int>prev(tar+1,0),curr(tar+1,0);
    // If index is 0 and number and tar both are 0
    if(arr[0] == 0){
        prev[0] = 2;
    }
    // If index is 0 but number is non-zero and tar is 0
    else{
        prev[0] = 1;
    }
    // writing arr[0] != 0 because we have already considered that case above
    if(arr[0] != 0 && arr[0] <= tar){
        prev[arr[0]] = 1;
    }
    for(int i=1;i<n;i++){
        for(int target=0;target<=tar;target++){
            int notPick = prev[target];
            int pick = 0;
            if(arr[i] <= target){
                pick = prev[target-arr[i]];
            }
            curr[target] = notPick + pick;
        }
        prev = curr;
    }
    return prev[tar];
}
int countPartitions(int n,int d,vector<int>&arr){
    int totalSum = 0;
    for(int i=0;i<n;i++){
        totalSum += arr[i];
    }
    if(totalSum-d < 0 || (totalSum-d)%2 != 0){
        return 0;
    }
    return solve((totalSum-d)/2,arr);
}
int targetSum(int n, int target, vector<int>& arr) {
    return countPartitions(n,target,arr);
}
```

