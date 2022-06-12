## Problem:

>Given a string str consisting of digits, one may group these digits into sub-groups while maintaining their original order.  
The task is to count number of groupings such that for every sub-group except the last one, sum of digits in a sub-group is less than or equal to sum of the digits in the sub-group immediately on its right.
For example, a valid grouping of digits of number 1119 is (1-11-9). Sum of digits in first subgroup is 1, next subgroup is 2, and last subgroup is 9. Sum of every subgroup is less than or equal to its immediate right.

## Example:

**Input:** 
```
str = "1119"
```
**Output:** 
```
7
```
**Explanation:** 
```
[1-119], [1-1-19], [1-11-9], [1-1-1-9], [11-19], [111-9] and [1119] are seven sub-groups.
```

## Recursion Tree for the above problem:

![](../GFG/Attachments/Pasted%20image%2020220612161736.png)

## Approach:

--> So here we can see that we have to track 2 thigs here: 1) Index and 2) PrevSum. and we will recursively go for every subsequence and then add it's integer value to the variable which will store `currSum` and if `currSum becomes more than PrevSum then we will make recursive call for i+1th index.`

--> Also we can use memoization here to avoid duplicate recursive calls. so we will first find the sum of all digits of the string and then make a dp array of `n+1 x sum+1` and initialise it with `-1`

## Memoized code:

```cpp
int solve(int idx,int prevSum,int n,string str,vector<vector<int>>&dp){
	    if(idx == n){
	        return 1;
	    }
	// If the ans is already calculated for the current call then we will directly take it from dp array.
	    if(dp[idx][prevSum] != -1){
	        return dp[idx][prevSum];
	    }
	    int ans = 0;
	    int currSum = 0;
	    for(int i=idx;i<n;i++){
			// Adding current element in currSum
	        currSum += str[i]- '0';
			// If currSum becomes greater than or equal to prevSum then we will call solve function with index i+1 and currSum will become prevSum.
	        if(currSum >= prevSum){
	            ans += solve(i+1,currSum,n,str,dp);
	        }
	    }
	    return dp[idx][prevSum] = ans;
	}
	int TotalCount(string str){
	    int n = str.size();
	    int sum = 0;
	    for(int i=0;i<n;i++)
	    {
	        sum+=(str[i]-'0');
	    }
	    vector<vector<int>>dp(n+1,vector<int>(sum+1,-1));
		// Initial call with index 0 and prevSum 0
	    return solve(0,0,n,str,dp);
	}
```