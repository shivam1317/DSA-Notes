## Problem Statement

>Given an array ‘ARR’, partition it into two subsets (possibly empty) such that their union is the original array. Let the sum of the elements of these two subsets be ‘S1’ and ‘S2’.
 Given a difference ‘D’, count the number of partitions in which ‘S1’ is greater than or equal to ‘S2’ and the difference between ‘S1’ and ‘S2’ is equal to ‘D’. Since the answer may be too large, return it modulo ‘10^9 + 7’.
 If ‘Pi_Sj’ denotes the Subset ‘j’ for Partition ‘i’. Then, two partitions P1 and P2 are considered different if:

```
1) P1_S1 != P2_S1 i.e, at least one of the elements of P1_S1 is different from P2_S2.
2) P1_S1 == P2_S2, but the indices set represented by P1_S1 is not equal to the indices set of P2_S2. Here, the indices set of P1_S1 is formed by taking the indices of the elements from which the subset is formed.
Refer to the example below for clarification.
```

## Example:

```
If N = 4, D = 3, ARR = {5, 2, 5, 1}
There are only two possible partitions of this array.
Partition 1: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
Partition 2: {5, 2, 1}, {5}. The subset difference between subset sum is: (5 + 2 + 1) - (5) = 3
These two partitions are different because, in the 1st partition, S1 contains 5 from index 0, and in the 2nd partition, S1 contains 5 from index 2.
```

## Approach:

--> Now we have 2 sums `s1` and `s2` and we can find total sum of elements and give it a name `totalSum`. Now `s1-s2` must be equal to `D` so we can write it like this:

```
s1-s2 = D
now s1 = totalSum-s2
totalSum - s2 - s2 = D
totalSum - D = 2s2
s2 = (totalSum - D)/2
```

--> So now we just have to find the `Count of subsets with sum equal to (totalSum-D)/2`

## Base case

1. If `totalSum-D` becomes negative
2. If `totalSum-D` is odd

--> So if any one of the above condition becomes true then we will return `0`

Otherwise we will run the `countOfSubsetWithGivenSum` code for `sum` equals to `totalSum-D`

## Memoized Code

```cpp
int solve(int i,int tar,vector<int>&arr,vector<vector<int>>&dp){
	if(i == 0){
		if(arr[i] == 0 && tar == 0){
			return 2;
		}
		if(tar == 0 || arr[i] == tar){
			return 1;
		}
		return 0;
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
	int totalSum = 0;
	for(int i=0;i<n;i++){
		totalSum += arr[i];
	}
	if(totalSum-d < 0 || (totalSum-d)%2 != 0){
		return 0;
	}
	return solve(n-1,(totalSum-d)/2,arr,dp);
}
```

## Tabulation Code

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
int main(){
	int totalSum = 0;
	for(int i=0;i<n;i++){
		totalSum += arr[i];
	}
	if(totalSum-d < 0 || (totalSum-d)%2 != 0){
		return 0;
	}
	return solve((totalSum-d)/2,arr,dp);
}
```

## Space optimised Code:

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
	}
	return prev[tar];
}
int main(){
	int totalSum = 0;
	for(int i=0;i<n;i++){
		totalSum += arr[i];
	}
	if(totalSum-d < 0 || (totalSum-d)%2 != 0){
		return 0;
	}
	return solve((totalSum-d)/2,arr,dp);
}
```

