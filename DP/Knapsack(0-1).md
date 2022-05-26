## Problem:

--> In this problem you have given one knapsack weight limit `W` and there are items in the house with `val` and `wt` and you have to take the values such that the value becomes `maximum` and it must not exceed the knapsack limit which is `W`.

## Example:

Input:

```
val = [30,40,60]
wt = [2,3,5]
W = 5
```

Ouput:

```
70
```

Explaination:

```
Here we can take val[0] and val[1] in our knapsack and get the maximum value of 70
```

## Approach:

--> Here we can't use greedy because there is no uniformity. So we have to find all possible ways which we can find using `recursion` using take and not take method and we will find maximum value.

we will start from `n-1`th index and go till 0
==> Base case:

If we reach at 0th index then we will have 2 conditions:
1. If val[0] is less than or equal to W then we will definitely take it.
2. If val[0] is greater than W then we can't take it.

So it will look like this in code:
```cpp
if(i == 0){
	// If we take it then the max value we can get will be val[0]
	if(val[0] <= W){
		return val[0];
	}
	else{
		return 0;
	}
}
```

## Recursive Code:

```cpp
if(i == 0){
	if(val[0] <= W){
		return val[0];
	}
	else{
		return 0;
	}
}
int notTake = solve(i-1,W);
int take = INT_MIN;
// If the weight of value is less than our capacity then only we can take it
if(wt[i] <= W){
	take = val[i] + solve(i-1,W-wt[i]);
}
return max(notTake,take);
```

## Complexity:

```
Time complexity: O(2^n)
Space complexity: O(n)
```

## Memoization Code:

```cpp
int solve(int i,vector<int>&val,vector<int>&wt,int W,vector<vector<int>>&dp){
	if(i == 0){
		if(wt[0] <= W){
			return val[0];
		}
		else{
			return 0;
		}
	}
	if(dp[i][W] != -1){
		return dp[i][W];
	}
	int notTake = solve(i-1,W);
	int take = INT_MIN;
	// If the weight of value is less than our capacity then only we can take it
	if(wt[i] <= W){
		take = val[i] + solve(i-1,W-wt[i]);
	}
	return dp[i][W] = max(notTake,take);
}

return max(notTake,take);
int main(){
	vector<vector<int>>dp(n,vector<int>(W+1,-1));
	return solve(n-1,val,wt,W,dp);
}
```

## Complexity:

```
Time complexity: O(nxW)
Space complexity: O(nxW) + O(n)
```

## Tabulation Code

```cpp
int solve(vector<int>&val,vector<int>&wt,int W){
	vector<vector<int>>dp(n,vector<int>(W+1,0));
	// Base case
	// For every value of W which is greater than wt[0] we can steal the value at index 0.
	// For example if W is 6 and wt[0] is 5 then we can take that value. Also if W is 7 and wt[0] then also we can take it so it means we can take the first value for all W=wt[0] to W
	for(int i=wt[0];i<=W;i++){
		dp[0][i] = val[0];
	}
	for(int i=1;i<n;i++){
		for(int w=0;w<=W;w++){
			int notPick = dp[i-1][w];
			int pick = INT_MIN;
			if(wt[i] <= w){
				pick = val[i] + dp[i-1][w-wt[i]]
			}
			dp[i][w] = max(notPick,pick);
		}
	}
	return dp[n-1][W];
}

int main(){
	return solve(val,wt,W);
}
```

## Space optimisation (Using 2 arrays):

```cpp
int knapsack(vector<int> wt, vector<int> value, int n, int W) 
{
	vector<int>prev(W+1),curr(W+1);
    for(int i=wt[0];i<=W;i++){
        prev[i] = value[0];
    }
    for(int i=1;i<n;i++){
        for(int w=0;w<=W;w++){
            int notPick = prev[w];
            int pick = INT_MIN;
            if(wt[i] <= w){
                pick = value[i]+ prev[w-wt[i]];
            }
            curr[w] = max(notPick,pick);
        }
        prev = curr;
    }
    return prev[W];
}
```

## Space optimisation (Using single array)

--> Here in `prev` and `curr` arrays the values for wt are dependent on the previous row and it's not dependent on other elements in the current array. So we can start traversing the prev array from right side and keep overwriting the values for `prev` for each `loop`

### Why we can't start from left to right?

--> Because if we start from left then when we do `W-wt[i]`, we can't find it on the left side of current element because it will be overwritten in current iteration.

So that's why we will use `single prev array` and do the space optimisation.

Code will look like this:

```cpp
int knapsack(vector<int> wt, vector<int> value, int n, int W) 
{
	vector<int>prev(W+1);
    for(int i=wt[0];i<=W;i++){
        prev[i] = value[0];
    }
    for(int i=1;i<n;i++){
        for(int w=W;w>=0;w--){
            int notPick = prev[w];
            int pick = INT_MIN;
            if(wt[i] <= w){
                pick = value[i]+ prev[w-wt[i]];
            }
            prev[w] = max(notPick,pick);
        }
    }
    return prev[W];
}
```

