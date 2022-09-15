## Problem statement:

Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for `'?'` and `'*'` where:

-   `'?'` Matches any single character.
-   `'*'` Matches any sequence of characters (including the empty sequence).

The matching should cover the **entire** input string (not partial).

## Example:

Example 1:

**Input:** 
```
s = "aa", p = "*"
```
**Output:** 
```
true
```
**Explanation:** 
```
'*' matches any sequence.
```

Example 2:

**Input:** 
```
s = "cb", p = "?a"
```
**Output:** 
```
false
```
**Explanation:** 
```
'?' matches 'c', but the second letter is 'a', which does not match 'b'.
```

## Approach:

--> In this problem, we have to match `p` with `s` so here we can use string matching method in which we use 2 variables `i and j` and check for each character if they are matching or not.

### If characters are matching:

Now here we also have one extra condition which will be `if p[i] is '?'` and if it's true then also we will consider it as match because `?` can match with any single character.

So for both of these conditions we will simply decrease both `i and j`.

```cpp
if(p[i] == s[j] || p[i] == '?'){
	return solve(i-1,j-1);
}
```

### If p[i] is '*':

--> now here we have 2 conditions:

1. If we assume `'*'` as sequence of length 0 (means empty string)
then we will simply decrease `i` and keep `j` as it is.
2. If we assume `'*'` as p[i]
then we will decrease `j`.

--> we have to do this for every character because `*` can have any length of subsequence so we will have check all possibilities:

this recursive tree will look like this:

![](../GFG/Attachments/Pasted%20image%2020220915182007.png)

```cpp
if(p[i] == '*'){
	return solve(i-1,j) || solve(i,j-1);
}
```

### If p[i] and s[j] are not matching:

then we will simply return `false`

## Base case:

--> So in base case, there can be 2 possibilities:

1. If we have traversed the p string means i is negative:

then we will check if `j is also negative` and if it is then we will return `true` because both strings got traversed and if `j is not negative` then we will return `false`.

```cpp
if(i<0){
	return j<0;
}
```

2. If we have traversed the s string means j is negative:

Here we can compare empty string with only one thing which is `'*'` so if p have all characters as `*` then we will return true otherwise we will return false.

```cpp
if(j<0){
	for(int k=0;k<=i;k++){
		if(p[k] != '*'){
			return false;
		}
	}
	return true;
}
```

## Recursive Code:

```cpp
 bool solve(int i,int j,string s,string p){
	if(i<0){
		return j<0;
	}
	if(j<0){
		for(int k=0;k<=i;k++){
			if(p[k] != '*'){
				return false;
			}
		}
		return true;
	}
	if(p[i] == s[j] || p[i] == '?'){
		return solve(i-1,j-1,s,p);
	}
	else if(p[i] == '*'){
		return solve(i-1,j,s,p) || solve(i,j-1,s,p);
	}
	// if they are not matching
	return false;
}
bool isMatch(string s, string p) {
	return solve(p.size()-1,s.size()-1,s,p);
}
```

## Memoization Code:

```cpp
bool solve(int i,int j,string s,string p,vector<vector<int>>&dp){
	if(i<0){
		return j<0;
	}
	if(j<0){
		for(int k=0;k<=i;k++){
			if(p[k] != '*'){
				return false;
			}
		}
		return true;
	}
	if(dp[i][j] != -1){
		return dp[i][j];
	}
	if(p[i] == s[j] || p[i] == '?'){
		return dp[i][j] = solve(i-1,j-1,s,p,dp);
	}
	else if(p[i] == '*'){
		return dp[i][j] = solve(i-1,j,s,p,dp) || solve(i,j-1,s,p,dp);
	}
	// if they are not matching
	return dp[i][j] = false;
}
bool isMatch(string s, string p) {
	int n = p.size(),m = s.size();
	vector<vector<int>>dp(n+1,vector<int>(m,-1));
	return solve(n-1,m-1,s,p,dp);
}
```

## Tabulation Code:

--> So in tabulation first we will write the base condition and also we have to change one thing which will ` we will use 1 based indexing` because in recursive code we are stopping at i or j becoming negative but we can't do it here so we will use 1 based indexing.

Now let's see all base cases one by one:

1. If i is 0 and j is also 0 then we will mark it as `true`
```cpp
dp[0][0] = true
```

2. if i is 0 and j is greater than 0 then we will mark it as `false`.

```cpp
for(int j=1;j<=m;j++){
	dp[0][j] = false;
}
```

3. if j is 0 then p must have all characters as `'*'` so that it can be matched with empty string.

```cpp
// starting from 1 because it's 1 based indexing.
for(int i=1;i<=n;i++){
	bool flag = true;
	for(int k=1;k<=i;k++){
		if(p[k-1] != '*'){
			flag = false;
			break;
		}
	}
	dp[i][0] = flag;
}
```

Now after base case we will just have to run one loop from i from `1 to n` and one nested loop for j from `1 to m` and just copy paste the logic from recursion code:

```cpp
bool isMatch(string s, string p) {
        int n = p.size(),m = s.size();
        vector<vector<bool>>dp(n+1,vector<bool>(m+1,false));
        // case 1
        dp[0][0] = true;
        // case 2
        for(int j=1;j<=m;j++){
            dp[0][j] = false;
        }
        // case 3
        for(int i=1;i<=n;i++){
            bool flag = true;
            for(int k=1;k<=i;k++){
                if(p[k-1] != '*'){
                    flag = false;
                    break;
                }
            }
            dp[i][0] = flag;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(p[i-1] == s[j-1] || p[i-1] == '?'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(p[i-1] == '*'){
                    dp[i][j] = dp[i][j-1] || dp[i-1][j];
                }else{
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }
```

## Space optimisation:

```cpp
bool isMatch(string s, string p) {
        int n = p.size(),m = s.size();
        vector<bool>prev(m+1,0),curr(m+1,0);
        // case 1
        prev[0] = true;
        // case 2
        for(int j=1;j<=m;j++){
            prev[j] = false;
        }
        for(int i=1;i<=n;i++){
	        // case 3
            bool flag = true;
            for(int k=1;k<=i;k++){
                if(p[k-1] != '*'){
                    flag = false;
                    break;
                }
            }
            curr[0] = flag;
            for(int j=1;j<=m;j++){
                if(p[i-1] == s[j-1] || p[i-1] == '?'){
                    curr[j] = prev[j-1];
                }else if(p[i-1] == '*'){
                    curr[j] = curr[j-1] || prev[j];
                }else{
                    curr[j] = false;
                }
            }
            prev = curr;
        }
        return prev[m];
    }
```