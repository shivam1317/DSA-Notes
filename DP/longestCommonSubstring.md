## problem:

>You have been given two strings 'STR1' and 'STR2'. You have to find the length of the longest common substring.
A string “s1” is a substring of another string “s2” if “s2” contains the same characters as in “s1”, in the same order and in continuous fashion also.

## Example:

```
If 'STR1' = “abcjklp” and 'STR2' = “acjkp”  then the output will be 3.

Explanation: The longest common substring is “cjk” which is of length 3.
```

## Approach:

--> if we take a look at tabulation matrix for strings `abcd` and `absd` then it will look like this:

![](../GFG/Attachments/Pasted%20image%2020220614223725.png)

--> here we will just check if s1[i] and s2[j] are same then we will just take a look at it's previous character means `diagonal in dp[i-1][j-1]` and if it have some value then we will take that value and add `1` in it.

--> So here we `only need continous elements` so we will make smaller change in the code for `longest common subsequence`

```cpp
if(s1[i-1] == s2[j-1]){
	dp[i][j] = 1 + dp[i-1][j-1];
}
else{
	// Don't need to go for not match condition because we only need continous elements.
	dp[i][j] = 0;
}
```

And finally `The maximum value in the entire matrix will be our answer`

## Code:

```cpp

	// Making dp array
	vector<vector<int>>dp(s1.size()+1,vector<int>(s2.size()+1,0));
	// for i==0
	for(int j=0;j<=s2.size();j++){
		dp[0][j] = 0;
	}
	// for j==0
	for(int i=0;i<=s1.size();i++){
		dp[i][0] = 0;
	}
	int ans = 0;
	for(int i=1;i<=s1.size();i++){
		for(int j=1;j<=s2.size();j++){
			if(s1[i-1] == s2[j-1]){
				dp[i][j] = 1 + dp[i-1][j-1];
				ans = max(ans,dp[i][j]);
			}
			else{
				dp[i][j] = 0;
			}
		}
	}
	return ans;
```

## Space optimisation:

```cpp

	// Making dp array
	vector<int>prev(s2.size()+1,0),curr(s2.size()+1,0);
	// for i==0
	for(int j=0;j<=s2.size();j++){
		prev[j] = 0;
	}
	// for j==0
	for(int i=0;i<=s1.size();i++){
		curr[0] = 0;
	}
	int ans = 0;
	for(int i=1;i<=s1.size();i++){
		for(int j=1;j<=s2.size();j++){
			if(s1[i-1] == s2[j-1]){
				curr[j] = 1 + prev[j-1];
				ans = max(ans,curr[j]);
			}
			else{
				curr[j] = 0;
			}
		}
		prev = curr;
	}
	return ans;
```