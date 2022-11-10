## Problem:

>You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
 Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.
 
## Example
```
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.
```

## Approach:

--> here we don't need to generate all subsets but we will run a recursion with our `index` and `target` and we will go till target becomes 0. and if target becomes 0 then that means we have a subset whose sum is same as target.

## base case

--> So there will be 2 base case

1. If target becomes 0
2. If index becomes 0

If index becomes 0 then we only have one value which is `arr[i]` and if that value is equal to `target` then we will return true otherwise we will return false.

Code will look like this:

```cpp
if(target == 0){
	return true;
}
if(i == 0){
	return arr[i] == target;
}
```

## Recursive solution

--> Now we have 2 options if we are at `i`th element.

```
1. Take the element in subset
2. Don't take it in subset
```

--> So if we don't take the element then we will just goto `i-1`th index. 
--> If we take the element then we have to check if `current element is less than target or not` because if the current element is bigger then we can't take it in sum because it will make our sum bigger than target.

Code for above logic will look like this:

```cpp
bool notTake = solve(i-1,target);
bool take = false;
if(target >= arr[i]){
	take = solve(i-1,target-arr[i]);
}
// Doing OR because we want only one subset with some K 
return notTake || take
```

## Memoization 

--> If we draw the recursion tree then we can see that there are overlapping subproblems and here we can use memoization.

So memoization code will look like this:

```cpp
int solve(int i,int target,vector<int>&arr,vector<vector<int>>&dp){
	if(target == 0){
		return true;
	}
	if(i == 0){
		return arr[i] == target;
	}
	if(dp[i][target] != -1){
		return dp[i][target];
	}
	bool notTake = solve(i-1,target);
	bool take = false;
	if(target >= arr[i]){
		take = solve(i-1,target-arr[i]);
	}
	return dp[i][target] = notTake || take;
}

int main(){
	// k is our target sum
	vector<vector<int>>dp(n,vector<int>(k+1,-1));
	cout<<solve(n-1,k,arr,dp);
}
```

## Tabulation Code

--> For first base case if target is equal to `0` then no matter what i is, the answer will be `true`

--> For second base case if i is equal to `0` then for only `target = arr[0]` it will be true 

Code :

```cpp
int solve(vector<int>&arr,int n){
	vector<vector<bool>>dp(n,vector<bool>(k+1,false));
	// first base case
	for(int i=0;i<n;i++){
		dp[i][0] = true;
	}
	// Second base case
	if(arr[0] <= k){
		dp[0][arr[0]] = true;
	}
	for(int i=1;i<n;i++){
		for(int target=1;target<=k;target++){
			bool notTake = dp[i-1][target];
			bool take = false;
			if(target >= arr[i]){
				take = dp[i-1][target-arr[i]];
			}
			dp[i][target] = take || notTake;
		}
	}
	return dp[n-1][k];
}
```

## Complexity:

```
Time complexity: O(Nxtarget)
Space complexity: O(Nxtarget)
```

## Space optmisation

--> here we just have to initialise `First element of each array as true` because we know that for `target = 0` the answer is true

Our `curr` and `prev` array size will be `k+1` 

```cpp
int solve(vector<int>&arr,int n){
	vector<bool>prev(k+1,false),curr(k+1,0);
	// first base case
	prev[0] = true;
	// Second base case
	if(arr[0] <= k){
		prev[arr[0]] = true;
	}
	for(int i=1;i<n;i++){
		curr[0] = true;
		for(int target=1;target<=k;target++){
			bool notTake = prev[target];
			bool take = false;
			if(target >= arr[i]){
				take = prev[target-arr[i]];
			}
			curr[target] = take || notTake;
		}
		prev = curr;
	}
	return prev[k];
}
```

## Complexity

```
Time complexity: O(Nxtarget)
Space complexity: O(target)
```

