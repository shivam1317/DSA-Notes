## Problem:

>Given a set of integers, find all distinct sums that can be generated from the subsets of the given sets.

## Example:

**Input:** 
```
nums = {1,2,3}
```
**Output:** 
```
{0,1,2,3,4,5,6}
```
**Explanation:** 
```
Seven distinct sum can be calculated
which are 0, 1, 2, 3, 4, 5 and 6.
0 if we do not choose any number.
1 if we choose only 1.
2 if we choose only 2.
3 if we choose only 3.
4 if we choose 1 and 3.
5 if we choose 2 and 3.
6 if we choose 1, 2 and 3.
```

## Approach:

--> So here we know that we have to find distinct sums of all possible subsequences so we can do it with `Pick and not pick method`. so in this method we will maintain 2 variables `i and tempSum` where `i` will traverse the array and `tempSum` will store the sum of picked elements. and when it comes to trying out all positions we have to use `recursion`.

So here we will maintain 4 things in parameters:
```
1. i
2. tempSum
3. nums array
4. set
```

>Here we need distinct elements that's why we are using set.

### Base case:

--> When i will become `nums.size()` then that means we have traversed whole array so we will add `tempSum` in our set and return.

```cpp
if(i >= nums.size()){
	s.insert(tempSum);
	return;
}
```

## Recursive Code:

```cpp
void solve(int i,int tempSum,vector<int>&nums,set<int>&s){
	if(i >= nums.size()){
		s.insert(tempSum);
		return;
	}
	
	// Pick
	solve(i+1,tempSum+nums[i],nums,s);
	// Not pick
	solve(i+1,tempSum,nums,s);
}
vector<int> DistinctSum(vector<int>nums){
	vector<int>ans;
	set<int>s;
	solve(0,0,nums,s);
	for(auto it:s){
		ans.push_back(it);
	}
	return ans;
}
```

--> But this code will give TLE so we have to optimise it further using memoization.

Here first we have to find the parameters for our dp array and that will be the parameteres which are changing.

These parameteres are:
```
i and tempSum
```

So we will make dp array of `max value for i x max value for tempSum` so we know the max value for i will be `nums.size()` and max value for tempSum will be `sum of all elements + 1`

And first we will mark all elements as `-1` and once we compute answer for it then we will mark it as `1`.

## Memoization Code:

```cpp
void solve(int i,int tempSum,vector<int>&nums,set<int>&s,vector<vector<int>>&dp){
	if(i >= nums.size()){
		s.insert(tempSum);
		return;
	}
	if(dp[i][tempSum] != -1){
		return;
	}
	
	// Pick
	solve(i+1,tempSum+nums[i],nums,s,dp);
	// Not pick
	solve(i+1,tempSum,nums,s,dp);
	dp[i][tempSum] = 1;
}
vector<int> DistinctSum(vector<int>nums){
	// Finding sum
	int sum = 0;
	for(auto it:nums){
		sum += it;
	}
	vector<int>ans;
	set<int>s;
	vector<vector<int>>dp(nums.size(),vector<int>(sum+1,-1));
	solve(0,0,nums,s,dp);
	// Adding all set elements into answer vector
	for(auto it:s){
		ans.push_back(it);
	}
	return ans;
}
```

#subsequence #memoization