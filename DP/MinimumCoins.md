## Problem Statement:

>You are given an array of ‘N’ distinct integers and an integer ‘X’ representing the target sum. You have to tell the minimum number of elements you have to take to reach the target sum ‘X’.

```
You have an infinite number of elements of each type.
```

## Example:

```
If N=3 and X=7 and array elements are [1,2,3]. 
Way 1 - You can take 4 elements  [2, 2, 2, 1] as 2 + 2 + 2 + 1 = 7.
Way 2 - You can take 3 elements  [3, 3, 1] as 3 + 3 + 1 = 7.
Here, you can see in Way 2 we have used 3 coins to reach the target sum of 7.
Hence the output is 3.
```

## Approach:

--> Here we can use `greedy` by simply taking the maximum number `X/maxNum` times and then take the other number likewise. But here greedy can be fail for examples like:

```
arr[] = [9,6,5,1]
X = 11
```

So here we will take `9` first greedily and then we will take `1` 2 times to make it `11` but here the current answer is `2` which is `6+5` so here because of `no uniformity` in elements we can't use greedy.

>Uniformity means something common in them, it can be difference of continues elements or anything.

So here we will find out all the possible ways which we can find with `recursion` and find the minimum number of coins.

--> So here we will use `pick and notPick` method and find all possible ways.

==> But there will be some base conditions:

If index is `0` then we have 2 conditions here:

1. If we can make target `X` using arr[0] 
2. If we can't make target `X` using arr[0]

For example we are at i=0 and the arr[0] is `6` and target is `7` then we can't make it using this element so we will return `INT_MAX`

But if arr[0] is 4 and target is 12 then we need `3` coins to make the target.

So here we will just check if target is divisible by arr[0] then we will return `target/arr[0]` otherwise we will return `1e9`

```cpp
if(i == 0){
	if(target % arr[0] == 0 && target >= arr[0]){
		return target/arr[0];
	}else{
		return 1e9;
	}
}
```

## Recursive code:

```cpp
int solve(int i,int target,vector<int>&coins){
	if(i == 0){
		if(target % arr[0] == 0 && target >= arr[0]){
			return target/arr[0];
		}
		else{
			return 1e9;
		}
	}
	int notPick = solve(i-1,target);
	int pick = INT_MAX;
	if(coins[i] <= target){
		// we have infinite supply of coins that's why we will again call the solve function for same index
		pick = 1+solve(i,target-coins[i]);
	}
	return min(notPick,pick);
}
```

## Complexity:

```
Time complexity: Exponential
Space complexity: O(target)
```

## Memoization code:

```cpp
int solve(int i,int target,vector<int>&coins,vector<vector<int>>&dp){
	if(i == 0){
		if(target % arr[0] == 0 && target >= arr[0]){
			return target/arr[0];
		}
		else{
			return 1e9;
		}
	}
	if(dp[i][target] != -1){
		return dp[i][target];
	}
	int notPick = solve(i-1,target);
	int pick = INT_MAX;
	if(coins[i] <= target){
		pick = 1+solve(i,target-coins[i]);
	}
	return dp[i][target] = min(notPick,pick);
}
int main(){
	vector<vector<int>>dp(n,vector<int>(target+1,-1));
	return solve(n-1,target,coins,dp);
}
```

## Complexity:

```
Time complexity: O(NxT)
Space complexity: O(NxT) + O(T)
```

## Tabulation Code:

```cpp
int solve(int target,vector<int>&coins){
	vector<vector<int>>dp(n,vector<int>(target+1,0));
	for(int t=1;t<=target;t++){
		if(t%coins[0] == 0 && t >= coins[0]){
			dp[0][t] = t/coins[0];
		}
		else{
			dp[0][t] = 1e9;
		}
	}
	for(int i=1;i<n;i++){
		for(int t=1;t<=target;t++){
			int notPick = dp[i-1][t];
			int pick = INT_MAX;
			if(coins[i] <= t){
				pick = 1 + dp[i][t-coins[i]];
			}
			dp[i][t] = min(notPick,pick);
		}
	}
	return dp[n-1][target];
}
```

## Space optimisation:

```cpp
int solve(int target,vector<int>&coins){
	vector<int>prev(target+1),curr(target+1);
	for(int t=1;t<=target;t++){
		if(t%coins[0] == 0 && t >= coins[0]){
			prev[t] = t/coins[0];
		}
		else{
			prev[t] = 1e9;
		}
	}
	for(int i=1;i<n;i++){
		for(int t=1;t<=target;t++){
			int notPick = prev[t];
			int pick = INT_MAX;
			if(coins[i] <= t){
				pick = 1 + curr[t-coins[i]];
			}
			curr[t] = min(notPick,pick);
		}
		prev = curr;
	}
	return prev[target];
}
```