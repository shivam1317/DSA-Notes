## Problem Statement:

>Given two strings `word1` and `word2`, return _the minimum number of operations required to convert `word1` to `word2`_.

You have the following three operations permitted on a word:
-   Insert a character
-   Delete a character
-   Replace a character


## Example:

**Input:** 
```
word1 = "horse", word2 = "ros"
```
**Output:** 
```
3
```
**Explanation:** 
```
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
```

## Approach:

--> Here we can follow string matching method where we will match every character and then we will have 2 conditions:

1. If they are matching:
	- then we will simply decrease both i and j 
	- we are not applying any step here
2. If they are not matching:
	- Then we have 3 possibilities here:
		- Insert s[j] character at that place
		- Delete this character and decrease i
		- Replace ith character with s[j]
		- we are applying any one of the step here so we will add 1 to total steps.

--> Let's see all these conditions in bit detail:

### If they are not matching:

1. If we insert s[j] character at that place:

Take a look at this example:

![](../GFG/Attachments/Pasted%20image%2020220915143912.png)

Here we will just decrease `j` because we have added jth character so they are matched.
```cpp
1 + solve(i,j-1);
```

2. If we delete the ith character:

Then we will simply decrease `i`.
```cpp
1 + solve(i-1,j);
```

3. If we replace the ith character:

Here we will ofcourse replace the ith character with s[j] and then they both will match and we will decrease both `i and j`.
```cpp
1 + solve(i-1,j-1);
```

At last take the `minimum` of these 3 steps:

### If they are matching:

just decrease both i and j but don't add 1 in steps because we haven't performed any step here.

```cpp
solve(i-1,j-1);
```

## Base case:

Here we will have 2 conditions:

1. If we have traversed all s1 string means i is negative and j is still have some value.
	- For example we have to make `ros` from `horse` and we have traversed whole horse string and j is at character `o` then we will have to make `ro` from empty string, so here we will perform `2 insert operations`.
	- so if i becomes negative then we will return `j+1`.
2. If we have traversed all s2 string means j is negative and i is still have some value.
	- For example in `ros and horse` we have traversed whole `ros` and i is at `r` character so that means we have to make empty string from `hor` so we will have to perform `3 deletion operation to make it empty string`. 
	- So if j becomes negative then we will return `i+1`.

```cpp
if(i < 0){
	return j+1;
}
if(j < 0){
	return i+1;
}
```

## Recursive code:

```cpp
int solve(int i,int j,string &s1,string &s2){
	if(i < 0){
		return j+1;
	}
	if(j < 0){
		return i+1;
	}
	if(s1[i] == s2[j]){
		return solve(i-1,j-1,s1,s2);
	}
	else{
		return 1 + min(min(solve(i,j-1,s1,s2),solve(i-1,j,s1,s2)), solve(i-1,j-1,s1,s2));
	}
}
```

## Memoization Code:

```cpp
int solve(int i,int j,string &s1,string &s2,vector<vector<int>>&dp){
	if(i < 0){
		return j+1;
	}
	if(j < 0){
		return i+1;
	}
	if(dp[i][j] != -1){
		return dp[i][j];
	}
	if(s1[i] == s2[j]){
		return dp[i][j] = solve(i-1,j-1,s1,s2,dp);
	}
	else{
		return dp[i][j] =  1 + min(min(solve(i,j-1,s1,s2,dp),solve(i-1,j,s1,s2,dp)), solve(i-1,j-1,s1,s2,dp));
	}
}
int main(){
	// n is size of s1 and m is size of s2
	vector<vector<int>>dp(n,vector<int>(m,-1));
	return solve(n-1,m-1,s1,s2,dp);
}
```

```
Time complexity: O(NxM)
Space complexity: O(NxM) + stack space of O(N+M)
```

## Tabulation Code:

--> Let's use tabulation to remove the stack space.

So in tabulation we just have to do one smaller change which will be `we will use 1 based indexing here` because in base case we are checking if i or j becomes negative but it's not possible here so that's why we will use 1 based indexing and our dp array size will be `N+1xM+1`

Also during checking the characters we will have to check like this:
```cpp
if(s1[i-1] == s2[j-1]);
```

Also in base case if `i` is 0 then we will add `j` for it instead of j+1 because we are following 1 based indexing and same for j also.

```cpp
int minDistance(string s1, string s2) {
        int n = s1.size(),m = s2.size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,0));
        // if j is 0
        for(int i=0;i<=n;i++){
            dp[i][0] = i;
        }
        // if i is 0
        for(int j=1;j<=m;j++){
            dp[0][j] = j;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = 1 + min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1]);
                }
            }
        }
        return dp[n][m];
    }
```

## Space optimisation:

--> Here we can see that we are only required previous row(dp[i-1]) and current row (dp[i]) to find answer for current row.

So we will make 2 separate arrays `prev and curr` which will act as rows and after each inner iteration, we will swap them.

Now here we can see for every `i=0` we have to put `0,1,2,3..` as j so we will initialise prev as `0,1,2,3...` and also for every `j=0` we have to put `0,1,2,3...` i.e every row's first element will be current index so after each inner iteration we will do `curr[0] = i`.

So let's optimise the space complexity:

```cpp
int minDistance(string s1, string s2) {
	int n = s1.size(),m = s2.size();
	vector<int>prev(m+1,0),curr(m+1,0);
	for(int j=1;j<=m;j++){
		prev[j] = j;
	}
	for(int i=1;i<=n;i++){
	// Initialising first element after each iteration
		curr[0] = i;
		for(int j=1;j<=m;j++){
			if(s1[i-1] == s2[j-1]){
				curr[j] = prev[j-1];
			}else{
				curr[j] = 1 + min(min(curr[j-1],prev[j]),prev[j-1]);
			}
		}
		// swapping prev and curr
		prev = curr;
	}
	return prev[m];
}
```

```
Time complexity: O(NxM)
Space complexity: O(M)
```

