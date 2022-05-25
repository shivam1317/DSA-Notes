## problem:

>You are given an array (0-based indexing) of **positive** integers and you have to tell how many different ways of selecting the elements from the array are there such that the sum of chosen elements is equal to the target number “tar”.

Note:

```
Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Input is given such that the answer will fit in a 32-bit integer.
```

## Example:

```
If N = 4 and tar = 3 and the array elements are [1, 2, 2, 3], then the number of possible ways are:
{1, 2}
{3}
{1, 2}
Hence the output will be 3.
```

## Approach:

--> This question is very similar to subset sum problem but here we just have to count the number of subsets. So we will start from `n-1` th index and go till `0` and we will use `pick and not pick` method.

## Base case:

--> If `i` becomes 0 then if `arr[i]==tar` then we will return `1` otherwise we will return `0`

--> If `tar` becomes `0` means we have found one subset with sum `tar` then we will return `1`

```cpp
if(tar == 0){
	return 1;
}
if(i == 0){
	return arr[i]==tar;
}
```

## Recursive Code:

```cpp
int solve(int i,int tar,vector<int>&arr){
	if(tar == 0){
		return 1;
	}
	if(i == 0){
		return arr[i] == tar;
	}
	int notPick = solve(i-1,tar,arr);
	int pick = 0;
	// we can't take bigger value than our target in subsetSum
	if(arr[i] <= tar){
		pick = solve(i-1,tar-arr[i],arr);
	}
	return notPick+pick;
}
int main(){
	return solve(n-1,tar,arr);
}
```

## Memoized code

--> Now we can optimise it using memoization because there are repetative calls.

```cpp
int solve(int i,int tar,vector<int>&arr,vector<vector<int>>&dp){
	if(tar == 0){
		return 1;
	}
	if(i == 0){
		return arr[i] == tar;
	}
	if(dp[i][tar] != -1){
		return dp[i][tar];
	}
	int notPick = solve(i-1,tar,arr);
	int pick = 0;
	// we can't take bigger value than our target in subsetSum
	if(arr[i] <= tar){
		pick = solve(i-1,tar-arr[i],arr);
	}
	return dp[i][tar] = notPick+pick;
}
int main(){
	vector<vector<int>>dp(n,vector<int>(tar+1,-1));
	return solve(n-1,tar,arr,dp);
}
```

## Tabulation Code

```cpp
int solve(int tar,vector<int>&arr){
	int n = arr.size();
	vector<vector<int>>dp(n,vector<int>(tar+1,0));
	for(int i=0;i<n;i++){
		dp[i][0] = 1;
	}
	if(arr[0] <= tar){
		dp[0][arr[0]] = 1;
	}
	for(int i=1;i<n;i++){
		for(int target=1;target<=tar;target++){
			int notPick = dp[i-1][target];
			int pick = 0;
			if(arr[i] <= target){
				pick = dp[i-1][target-arr[i]];
			}
			dp[i][target] = notPick + pick;
		}
	}
	return dp[n-1][tar];
}
```

## Space optmisation 

```cpp
int solve(int tar,vector<int>&arr){
	int n = arr.size();
	vector<int>prev(tar+1,0),curr(tar+1,0);
	prev[0] = 1;
	if(arr[0] <= tar){
		prev[arr[0]] = 1;
	}
	for(int i=1;i<n;i++){
		curr[0] = 1;
		for(int target=1;target<=tar;target++){
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
```

## What if the array contains 0 also?

--> This is the another case where array elements can contain `0` also. Since the contrains for the above question was `1<=arr[i]<=1e5` but if we get different constrains then we have to change our logic a bit.

--> So if we take 0 or not take, it's not gonna make any change to subset sum. So we just have to find all number of zeros and then find the number of ways in which 0 can be placed and we can find it using `pow(2,n)` where `n` is the count of zeros.

But there is a another case,

If we see this line in memoized code:

```cpp
if(tar == 0){
	return 1;
}
```

--> So here suppose array is `[0,0,1]` and if we make call for taking `1` then the another call will be for `[0,0]` with the target 0 but here in code we have written the condition if `tar` becomes 0 then just return 1 and we are not considering the other zeros.

So that's why we should not stop if `tar` becomes 0 and instead we have to go till `i` becomes 0.

So if we remove the above code then we have 3 conditions.

1. If arr[i] is equal to 0 and target is 0 so we have total `2` ways: take it and not but in both ways it's not gonna make any change in target so we will return `2` for this condition.
2. If arr[i] is not 0 and target is 0 then we have only one choice which is `Don't take it` so we will return 1.
3. If arr[i] is not 0 and target is also not 0 then we just have to check if both are same or not. If both are same then return 1 otherwise return 0.

So this condition will be changed to:

```cpp
if(i == 0){
	if(arr[i] == 0 && tar == 0){
		return 2;
	}
	// Condition 2 and 3 in single if condition because both are returning 1
	if(tar == 0 || arr[i] == tar){
		return 1;
	}
	return 0;
}
```

==> Tabulation Code for this will look like this:


```cpp
int solve(int tar,vector<int>&arr){
	int n = arr.size();
	vector<vector<int>>dp(n,vector<int>(tar+1,0));
	// If index is 0 and number and tar both are 0
	if(arr[0] == 0){
		dp[0][0] = 2;
	}
	// If index is 0 but number is non-zero and tar is 0
	else{
		dp[0][0] = 1;
	}
	// writing arr[0] != 0 because we have already considered that case above
	if(arr[0] != 0 && arr[0] <= tar){
		dp[0][arr[0]] = 1;
	}
	for(int i=1;i<n;i++){
		for(int target=0;target<=tar;target++){
			int notPick = dp[i-1][target];
			int pick = 0;
			if(arr[i] <= target){
				pick = dp[i-1][target-arr[i]];
			}
			dp[i][target] = notPick + pick;
		}
	}
	return dp[n-1][tar];
}
```