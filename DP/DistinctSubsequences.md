## Problem statement:

![](../GFG/Attachments/Pasted%20image%2020220914182703.png)

## Example:

![](../GFG/Attachments/Pasted%20image%2020220914182736.png)

## Approach:

--> So here we have 2 possibilities for every character in string `S`, whether we take it or leave it. And when it comes to pick and not pick method we will always use `recursion`.

--> So we will make 2 variables, `i and j` where i will traverse `S1`(which is big string) and `j` will traverse `S2`. and we will start from end of the strings and now we will check whether they are same or not.

- If s[i] and s[j] are same:
	- Then we will have another 2 conditions:
		1. If we consider current character then we will decrease both i and j by 1.
		2. If we don't want to take the current element then we will just decrease i by 1.
- If they are not same:
	- Then we will decrease i by 1.

==> It will look like this in code:

```cpp
if(s[i] == s[j]){
	return solve(i-1,j-1) + solve(i-1,j);
}else{
	return solve(i-1,j);
}
```

### Base case:

--> Whenever we find any question saying `find all possible ways` then the base case will always return `1 or 0`. 

- If our j becomes negative means we have traversed whole `S` string then we know that we have found one valid subsequence so we will return 1.
- If our i becomes negative and j is not negative then we will return 0.

```cpp
if(j<0){
	return 1;
}
if(i<0){
	return 0;
}
```

## Recursive Code:

```cpp
int solve(int i,int j,string &t,string &s){
    if(j<0){
        return 1;
    }
    if(i<0){
        return 0;
    }
    if(t[i] == s[j]){
        return solve(i-1,j-1,t,s) + solve(i-1,j,t,s);
    }else{
        return solve(i-1,j,t,s);
    }
}
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    return solve(lt-1,ls-1,t,s);
} 
```

## memoization code:

```cpp
int solve(int i,int j,string &t,string &s,vector<vector<int>>&dp){
    if(j<0){
        return 1;
    }
    if(i<0){
        return 0;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    if(t[i] == s[j]){
        return dp[i][j] = solve(i-1,j-1,t,s,dp) + solve(i-1,j,t,s,dp);
    }else{
        return dp[i][j] = solve(i-1,j,t,s,dp);
    }
}
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    vector<vector<int>>dp(lt,vector<int>(ls,-1));
    return solve(lt-1,ls-1,t,s,dp);
} 
```

## Tabulation code:

--> Now here we will do some minor change in base case because we are stopping when i or j becomes negative but in tabulation we start from opposite side means from `0` so here we will have to follow `1 based indexing.`

So our base case will be like this:

```cpp
// If j is 0 then we will mark it as 1
for(int i=0;i<t.size();i++){
	dp[i][0] = 1;
}
// we will initialise our dp array with 0 so no need to write loop for j
```

Now during comparing we will just compare it like this:

```
if(t[i-1] == s[j-1])
```
because we have followed 1 based indexing.

```cpp
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    vector<vector<long long>>dp(lt+1,vector<long long>(ls+1,0));
    int mod = 1e9+7;
    for(int i=0;i<=lt;i++){
        dp[i][0] = 1;
    }
    for(int i=1;i<=lt;i++){
        for(int j=1;j<=ls;j++){
            if(t[i-1] == s[j-1]){
                dp[i][j] = dp[i-1][j-1]%mod + dp[i-1][j]%mod;
            }else{
                dp[i][j] = dp[i-1][j]%mod;
            }
        }
    }
    return (int)dp[lt][ls]%mod;
} 
```

## Space optimisation:

```cpp
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    vector<long long>prev(ls+1,0),curr(ls+1,0);
    int mod = 1e9+7;
    // we are initialising first element of every column as 1 so here also we will initialise both array's first element as 1 and leave other as 0.
    prev[0] = curr[0] = 1;
    for(int i=1;i<=lt;i++){
        for(int j=1;j<=ls;j++){
            if(t[i-1] == s[j-1]){
                curr[j] = prev[j-1]%mod + prev[j]%mod;
            }else{
                curr[j] = prev[j]%mod;
            }
        }
        prev = curr;
    }
    return (int)prev[ls]%mod;
} 
```

## Further optimisation:

--> Here we can see that to compute `curr[j]` we are requiring `prev[j-1] and prev[j]` and then once this loop completes, we are using this curr as prev. so why don't we store this `prev[j]` value in prev itself and use it to find another values.

It will look like this in code:

```cpp
if(t[i-1] == s[j-1]){
	prev[j] = prev[j-1]%mod + prev[j]%mod;
}
// The below part is not needed anymore
//else{
//	prev[j] = prev[j]%mod;
//}
```

Full Code:

```cpp
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    vector<long long>prev(ls+1,0);
    int mod = 1e9+7;
    prev[0] = 1;
    for(int i=1;i<=lt;i++){
    // we are running this backwards because we need previous value to count current and also if we run it from 0 to n then it will replace our current value to find the next value.
        for(int j=ls;j>=0;j--){
            if(t[i-1] == s[j-1]){
                prev[j] = prev[j-1]%mod + prev[j]%mod;
            }
        }
    }
    return (int)prev[ls]%mod;
} 
```