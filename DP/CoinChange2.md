## Problem:

> You are given an infinite supply of coins of each of denominations D = {D0, D1, D2, D3, ...... Dn-1}. You need to figure out the total number of ways W, in which you can make a change for value V using coins of denominations from D. Print 0, if a change isn't possible.

## Example:

Input:

```
3
1 2 3
4
```

Output:

```
4
```

Explaination:

```
We can make a change for the value V = 4 in four ways.
1. (1,1,1,1),
2. (1,1, 2), [One thing to note here is, (1, 1, 2) is same as that of (2, 1, 1) and (1, 2, 1)]
3. (1, 3), and
4. (2, 2)
```

## Approach:

--> here we will find all possible ways using `recursion` and then we will use take and notTake method and return total count of `take and notTake`.

Also here we have infinite number of coins so we have to take that in mind also.

### Base case:

If we reach at 0 index then we can only make that number if `target%arr[0]` is 0. So for example if at index 0, target is `5` and arr[0] is `2` then we can't make it. If target is `6` and arr[0] is `2` then we can make it using only one way which is `[2,2,2]`

So base case will look like this:

```cpp
if(i == 0){
	return target%arr[0] == 0;
}
```

## Recursive Code:

```cpp
int solve(int i,int target,vector<int>&arr){
	if(i == 0){
		return target%arr[0] == 0;
	}
	int notPick = solve(i-1,target,arr);
	int pick = 0;
	if(arr[i] <= target){
		pick = solve(i,target-arr[i],arr);
	}
	return notPick+pick;
}
```

## memoization:

```cpp
int solve(int i,int target,vector<int>&arr){
	if(i == 0){
		return target%arr[0] == 0;
	}
	if(dp[i][target] != -1){
		return dp[i][target];
	}
	int notPick = solve(i-1,target,arr,dp);
	int pick = 0;
	if(arr[i] <= target){
		pick = solve(i,target-arr[i],arr,dp);
	}
	return dp[i][target] = notPick+pick;
}
int main(){
	vector<vector<int>>dp(n,vector<int>(target+1,-1));
	return solve(n-1,target,arr,dp);
}
```

## Tabulation

```cpp
int solve(int target,vector<int>&arr){
	vector<vector<int>>dp(n,vector<int>(target+1,0));
	for(int i=0;i<=target;i++){
		if(i%arr[0] == 0){
			dp[0][i] = 1;
		}
		else{
			dp[0][i] = 0;
		}
	}
	for(int i=1;i<n;i++){
		for(int t=0;t<=target;t++){
			int notPick = dp[i-1][t];
			int pick = 0;
			if(arr[i] <= t){
				pick = dp[i][t-arr[i]];
			}
			dp[i][t] = notPick + pick;
		}
	}
	return dp[n-1][target];
}
```

## Space optimisation

```cpp
int solve(int target,vector<int>&arr){
	vector<int>prev(target+1),curr(target+1);
	for(int i=0;i<=target;i++){
		if(i%arr[0] == 0){
			prev[i] = 1;
		}
		else{
			prev[i] = 0;
		}
	}
	for(int i=1;i<n;i++){
		for(int t=0;t<=target;t++){
			int notPick = prev[t];
			int pick = 0;
			if(arr[i] <= t){
				pick = curr[t-arr[i]];
			}
			curr[t] = notPick + pick;
		}
		prev = curr;
	}
	return prev[target];
}
```

#dp #greedy 