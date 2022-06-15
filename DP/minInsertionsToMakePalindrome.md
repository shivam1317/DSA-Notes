## Problem:

>A palindrome string is one that reads the same backward as well as forward. Given a string 'STR', you need to tell the minimum number of characters needed to insert into it to make it a palindromic string.

## Example:

```
String 'STR' = “abcaa” can be converted into a palindrome by inserting 2 characters. So the final string becomes “aabcbaa”.
```

## Approach:

--> in the string `abcaa` we can see that we just have to add `b and c` to make it `abcacba`. so here first we just have to find the `longest palindromic subsequence` and which will be `aaa` in this case and then just take it's length and subtract it from original string's length which will be `5-3 = 2` and it's our answer.

## Code:

```cpp
#include<bits/stdc++.h>
int solve(string s1,string s2){
    vector<vector<int>>dp(s1.size()+1,vector<int>(s2.size()+1,0));
    // for i==0
    for(int j=0;j<=s2.size();j++){
        dp[0][j] = 0;
    }
    // for j==0
    for(int i=0;i<=s1.size();i++){
        dp[i][0] = 0;
    }
    for(int i=1;i<=s1.size();i++){
        for(int j=1;j<=s2.size();j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
	// Just this small change in longest common subsequence code
    return s1.size()-dp[s1.size()][s2.size()];
}
int minInsertion(string &s1)
{
    string s2 = s1;
    reverse(s2.begin(),s2.end());
    return solve(s1,s2);
}
```