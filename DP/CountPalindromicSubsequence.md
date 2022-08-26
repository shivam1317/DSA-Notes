## problem:

>Given a string str of length N, you have to find number of palindromic subsequence (need not necessarily be distinct) which could be formed from the string str.  
Note: You have to return the answer module 109+7;

## Example:

**Input:** 
```
Str = "aab"
```
**Output:** 
```
4
```
**Explanation:**
```
palindromic subsequence are : "a", "a", "b", "aa"
```

## Approach:

--> In this problem we need total subsequences and for that we have to try all possible ways and when it comes to finding all possible ways we know we have to use `Recursion`.

So here we will use 2 pointers `i and j` and we will start i from 0 and j from `n-1` where n will be length of string. Now we will have 2 conditions:

```
1. If str[i] and str[j] are same
2. If str[i] and str[j] are not same
```

--> If they both are same then we know that `we found one valid palindrome` so we will add `1` to our count and make call for both conditions `fun(i+1,j) and fun(i,j-1)`.

```cpp
ans += 1 + f(i+1,j) + f(i,j-1);
```

--> If they are not same then we will make call for both conditions `fun(i+1,j) and fun(i,j-1)` but here we also have to `subtract fun(i+1,j-1)` because the above 2 function calls will consider the `(i+1,j-1)th` value twice so we have to subtract it once.

```cpp
ans += f(i+1,j) + f(i,j-1) - f(i+1,j-1);
```

Let's see it in diagram for example `abc`:

![](../GFG/Attachments/Pasted%20image%2020220826173103.png)

In the diagram we can see that `b` is repeating twice in both function calls so we have to subtract it one time. 

### But why we haven't subtracted f(i+1,j-1) when arr[i] and arr[j] are same?

--> Let's take an example of `aba` here the 2 function calls will be `ab and ba` and here also b is repeating 2 times but here we know that first and last characters are same so we have to take `aba` as a valid palindrome and `aa` is also a valid palindrome.

## Base case:

--> There will be 2 base cases:

1. If i == j,
	- means there is only 1 character and it's a valid palindrome so we will return `1`
2. If i > j,
	- means we have traversed all characters of string so we will return `0`.

## Recursion Code:

```cpp
long long ans = 0;
long long solve(int i,int j,string s){
	if(i > j){
		return 0;
	}
	if(i == j){
		return 1;
	}
	if(s[i] == s[j]){
		ans += solve(i+1,j,s) + solve(i,j-1,s) + 1;
	}
	else{
		ans += solve(i+1,j,s) + solve(i,j-1,s) - solve(i+1,j-1,s);
	}
}
// At last return ans
```

--> But the above code will give `TLE` so we have to use memoization here and optimise it!

## Memoization Code:

```cpp
int mod = 1e9+7;
long long int solve(int i,int j,string str,vector<vector<long long>>&dp){
	if(i > j){
		return 0;
	}
	if(i == j){
		return 1;
	}
	if(dp[i][j] != -1){
		return dp[i][j];
	}
	if(str[i] == str[j]){
		return dp[i][j] = (solve(i+1,j,str,dp) + solve(i,j-1,str,dp) + 1)%mod;
	}else{
		return dp[i][j] = ((solve(i+1,j,str,dp) + solve(i,j-1,str,dp)) - solve(i+1,j-1,str,dp) + mod)%mod;
	}
}
long long int  countPS(string str)
{
	int n = str.length();
   vector<vector<long long>>dp(n,vector<long long>(n,-1));
   return solve(0,n-1,str,dp)%mod;
}
```

--> we are adding `mod` in else condition to avoid overflow because we are subtracting `solve(i+1,j-1,str,dp)` and the value can become negative if we don't do that.

==> But still this code gave TLE 😔 so let's optimise it.

we just have to `pass the string by reference` like this:

```cpp
long long solve(int i,int j,string &str,vector<vector<long long>>&dp)
```