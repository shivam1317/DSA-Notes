## Problem:

>Given two strings, 'S' and 'T' with lengths 'M' and 'N', find the length of the 'Longest Common Subsequence'.
For a string 'str'(per se) of length K, the subsequences are the strings containing characters in the same relative order as they are present in 'str,' but not necessarily contiguous. Subsequences contain all the strings of length varying from 0 to K.

## Example:

### Sample Input 1 :

```
adebc
dcadb
```

### Sample Output 1 :

```
3
```

### Explanation Of The Sample Output 1 :

```
Both the strings contain a common subsequence 'adb', which is the longest common subsequence with length 3. 
```

## Approach:

--> So first step in every DP problem is to convert the problem in the terms of indexes. so here `we can't use same index on both strings` because we have to iterate both strings on different indexes also. so we will use 2 indexes `i1 and i2`.

So now for each character in string we have 2 conditions:

```
1. If both characters matches
2. If they don't match
```

--> If s1[i1] and s2[i2] matches then we will just add `1` in our answer and make recursive call for `i1-1` and `i2-1`

--> If they don't match them also we have some things to consider:

Suppose we have 2 strings like `ab` and `ba` and here we can see s1[1] and s2[1] are not mathing.

```
1. we can't move both i1 and i2 because s1[i1] can match at any point in s2 so maybe it get skipped if we move both i1 and i2 at the same time.
2. we have to move both i1 and i2 one by one to check if they find the character as same as them in their opposite string.
```

--> The below diagram will clear everything.

![](../GFG/Attachments/Pasted%20image%2020220614190512.png)

It will look like this in code:

```cpp
if(s1[i1] == s2[i2]){
	return 1 + solve(i1-1,i2-1);
}
// If not match
return 0 + max(solve(i1-1,i2),solve(i1,i2-1));
```

## Base case:

--> Now we are decreasing `ind1` and `ind2` by `1` in code but suppose `ind1` is `0` and `ind2` is `2` so after this iteration ind1 will become `negative` so we can't have negative indexes so it means it's the end of index so we will simply return `0`.

```cpp
if(ind1 < 0 || ind2 < 0){
	return 0;
}
```

==> SO final recursive code will look like this:

## Recursive Code:

```cpp
int solve(int idx1,int idx2,string s1,string s2){
	if(ind1 < 0 || ind2 < 0){
		return 0;
	}
	if(s1[idx1] == s2[idx2]){
		return 1 + solve(idx1-1,idx2-1,s1,s2);
	}
	return max(solve(idx1-1,idx2,s1,s2),solve(idx1,idx2-1,s1,s2));
}
```

## Memoization

--> Since the previous solution will have exponantial time complexity, it will give TLE so have to convert it to memoized form.

the max value for `ind1` will be size of s1 and max value for `ind2` will be size of s2.

```cpp
int solve(int idx1,int idx2,string s1,string s2){
	if(idx1 < 0 || idx2 < 0){
		return 0;
	}
	if(dp[idx1][idx2] != -1){
		return dp[idx1][idx2];
	}
	if(s1[idx1] == s2[idx2]){
		return dp[idx1][idx2] = 1 + solve(idx1-1,idx2-1,s1,s2);
	}
	return dp[idx1][idx2] = max(solve(idx1-1,idx2,s1,s2),solve(idx1,idx2-1,s1,s2));
}
int main(){
	vector<vector<int>>dp(s1.size(),vector<int>(s2.size(),-1));
	return solve(s1.size()-1,s2.size()-1,s1,s2);
}
```

## Complexity:

```
Time complexity: O(NxM)
Space comeplexity: O(NxM) + O(N+M)
```

## Tabulation Code:

--> The base condition for tabulation is bit tricky. In this problem we return 0 when we reach negative index but we can't do it here. For example in base case index becomes `-1` then we can't do like `dp[-1]` because that's not possible.

==> So we will use shifting of index, Means we will make initial call for `n,m` instead of making call for `n-1,m-1`. and now our base case will be when ind1 or ind2 becomes 0. So now we are treating `i as i-1` and `j as j-1` in code.

So final tabulation code will look like this:

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
	return dp[s1.size()][s2.size()];
}
```

## Space optimisation Code:

```cpp
int lcs(string s, string t)
{
	int n = s.size();
    int m = t.size();
    vector<int>prev(m+1,0),curr(m+1,0);
    for(int j=0;j<=m;j++){
        prev[j] = 0;
    }
    for(int i=0;i<=n;i++){
        curr[0] = 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i-1] == t[j-1]){
                curr[j] = 1 + prev[j-1];
            }else{
                curr[j] = max(prev[j],curr[j-1]);
            }   
        }
        prev = curr;
    }
    return prev[m];
}
```

## Printing Longest Common Subsequence

--> Now if we print the `dp` array for strings `adebc` and `dcadb` then it will look like this:

```
0 0 0 0 0 0
0 0 0 1 1 1
0 1 1 1 2 2
0 1 1 1 2 2
0 1 1 1 2 3
0 1 2 2 2 3
```

--> Now here we will start from `dp[5][5]` and move in grid using these 2 conditions:

```
1. For any dp[i][j], if s1[i] and s2[j] are same then they must came from dp[i-1][j-1] call so we will goto dp[i-1][j-1] and also add s1[i] in our answer string.
2. For any dp[i][j], if s1[i] and s2[j] are different then they must came from the maximum value of dp[i-1][j] and dp[i][j-1] so we will also find the maximum of them and goto that cell. But this time we will not add that character in our answer string because they are different.
```

--> The whole process will be look like the below diagram:

![](../GFG/Attachments/Pasted%20image%2020220614211300.png)

==> So final code will look like this:

## Code

```cpp
// After getting DP array with longest common subsequence code
int i = n,j=m;
string ans = "";
while(i > 0 && j>0){
	if(s1[i-1] == s2[j-1]){
		// Add this character in our answer string
		ans += s1[i-1];
		// Go diagonal
		i--;
		j--;
	// Finding max between dp[i-1][j] and dp[i][j-1]
	}else if(dp[i-1][j] > dp[i][j-1]){
		i--;
	}else{
		j--;
	}
}
// reverse the string
reverse(ans.begin(),ans.end());
return ans;
```

## Complexity:

```
Time complexity: O(NxM)
```

