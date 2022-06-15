## problem:

>You are given 2 non-empty strings “str” and “ptr” consisting of lowercase English alphabets only. Your task is to convert string “str” into string “ptr”. In one operation you can do either of the following on “str”:
Remove a character from any position in “str”.
Add a character to any position in “str”.
You have to find the minimum number of operations required to convert string “str” into “ptr”.

## Example:

```
If str = “abcd”, ptr = “anc”
In one operation remove str[3], after this operation str becomes “abc”.    
In the second operation remove str[1], after this operation str becomes “ac”.
In the third operation add ‘n’ in str[1], after this operation str becomes “anc”.

Hence, the output will be 3.
```

## Approach:

--> If we analyse the above test case then here we have to keep 2 things in mind:

```
1. we only have to add the characters which are not into str but they are in ptr
2. we have to remove the characters which are into str but not into ptr
```

--> So that means we will not touch the already present characters in both strings and we can find such characters using `longest common subsequence`. and after finding it's length we will just subtract that length from `str.size()` and `ptr.size()` and our final equation will like this:

```cpp
return (str.size()-dp[n][m]) + (ptr.size()-dp[n][m]);
```

## Code:

```cpp
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
	int n = s1.size();
	int m = s2.size();
    return (n-dp[n][m]) + (m-dp[n][m]);
}
int main(){
	return solve(s1,s2);
}
```

