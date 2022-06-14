## Problem:

>Given a rod of length ‘N’ units. The rod can be cut into different sizes and each size has a cost associated with it. Determine the maximum cost obtained by cutting the rod and selling its pieces.

Note:

```
1. The sizes will range from 1 to ‘N’ and will be integers.
2. The sum of the pieces cut should be equal to ‘N’.
3. Consider 1-based indexing.
```

## Example:
### Sample Input:

```
2
5
2 5 7 8 10
8
3 5 8 9 10 17 17 20
```

### Sample Output:

```
12
24
```

### Explaination:

```
Test case 1:

All possible partitions are:
1,1,1,1,1           max_cost=(2+2+2+2+2)=10
1,1,1,2             max_cost=(2+2+2+5)=11
1,1,3               max_cost=(2+2+7)=11
1,4                 max_cost=(2+8)=10
5                   max_cost=(10)=10
2,3                 max_cost=(5+7)=12
1,2,2               max _cost=(1+5+5)=12    

Clearly, if we cut the rod into lengths 1,2,2, or 2,3, we get the maximum cost which is 12.


Test case 2:

Possible partitions are:
1,1,1,1,1,1,1,1         max_cost=(3+3+3+3+3+3+3+3)=24
1,1,1,1,1,1,2           max_cost=(3+3+3+3+3+3+5)=23
1,1,1,1,2,2             max_cost=(3+3+3+3+5+5)=22
and so on….

If we cut the rod into 8 pieces of length 1, for each piece 3 adds up to the cost. Hence for 8 pieces, we get 8*3 = 24.
```

## Approach:

--> Let's convert this problem into completly opposite. let's say we have n rod parts and we have to make rod of length n. each rod part have it's length (which will be index+1) and the price.

--> So here `this problem becomes similar to unbounded knapsack` because we have infinite number of rods so that we can take as many as rod parts we want to make a final rod of length `n`

So we will have 2 conditions:

```
1. Don't take the current rod part in final rod.
2. Take the current rod part in final rod.
--> And we can only take it if length of current rod part is lower than or equal to n
```

So it will look like this in code:

```cpp
int notTake = solve(idx-1,n);
int take = INT_MIN;
int currRodLength = idx+1;
if(currRodLength <= n){
	take = arr[idx] + solve(idx,n-currRodLength);
}
return max(notTake,take);
```

## Base case:

--> When we reach `0` then suppose we have target as `5` and we know that for index 0, the length will be `1` so we will require `5` rod parts to make target length and the price will be `arr[0]*target` and that's what we will return.

```cpp
if(idx == 0){
	return arr[0]*target;
}
```

## Recursive code:

```cpp
int solve(int idx,vector<int>arr,int target){
	if(idx == 0){
		return arr[0]*target;
	}
	int notPick = solve(idx-1,arr,target);
	int pick = INT_MIN;
	int currRodLength = idx+1;
	if(currRodLength <= target){
		pick = arr[idx] + solve(idx,arr,target-currRodLength);
	}
	return max(notPick,pick);
}
int main(){
	return solve(n-1,arr,target);
}
```

## Memoized Code:

```cpp
int solve(int idx,vector<int>arr,int target){
	if(idx == 0){
		return arr[0]*target;
	}
	if(dp[idx][target] != -1){
		return dp[idx][target];
	}
	int notPick = solve(idx-1,arr,target);
	int pick = INT_MIN;
	int currRodLength = idx+1;
	if(currRodLength <= target){
		pick = arr[idx] + solve(idx,arr,target-currRodLength);
	}
	return dp[idx][target] = max(notPick,pick);
}
int main(){
	vector<vector<int>>dp(n,vector<int>(target+1,-1));
	return solve(n-1,arr,target,dp);
}
```

## Complexity:

```
Time complexity: O(Nxtarget)
Space complexity: O(Nxtarget) + O(target)
```

## Tabulation code

```cpp
int solve(vector<int>&arr,int target){
	vector<vector<int>>dp(arr.size(),vector<int>(target+1,0));
	for(int i=0;i<=target;i++){
		dp[0][i] = arr[0]*i;
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<=target;j++){
			int notPick = dp[i-1][j];
			int pick = INT_MIN;
			if(i+1 <= j){
				pick = dp[i][j-(i+1)];
			}
			dp[i][j] = max(notPick,pick);
		}
	}
	return dp[n-1][target];
}
int main(){
	return solve(arr,target);
}
```

## Complexity:

```
Time complexity: O(N*target)
Space complexity: O(N*target)
```

## Space optmisation:

```cpp
int cutRod(vector<int> &price, int target)
{
    int n = price.size();
	vector<int>prev(target+1,0),curr(target+1,0);
    for(int i=0;i<=target;i++){
        prev[i] = price[0]*i;
    }
    for(int i=1;i<price.size();i++){
        for(int j=0;j<=target;j++){
            int notTake = prev[j];
            int pick = INT_MIN;
            if(i+1 <= j){
                pick = price[i] + curr[j-(i+1)];
            }
            curr[j] = max(notTake,pick);
        }
        prev = curr;
    }
    return prev[target];
}
```

