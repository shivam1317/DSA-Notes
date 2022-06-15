## Problem:

>In this problem you have given one string and you have to find a longest palindromic subsequence from it's all subsequences.

## Example:

suppose you have a string `bbabcbcab` then it's all palindromic subsequences will be:

```
bb
bbb
bbbb
bab
bcb
babcbab
aca
And so on...
```

--> But here we want `longest palindromic subsequence` so here longest subsequence will be `babacbab` which have length `7` so we will return 7 as answer.

## Approach:

--> Here if we analyse the answer from above explaination then we can see that the subsequence contains one character from front and that same character from back.

This diagram will clear this:

![](../GFG/Attachments/Pasted%20image%2020220615140842.png)

>The same color character defines that one is taken from starting of string and one is taken from ending of string.

==> So here we can take `2` strings: 1) Original string and 2) Reversed string and then find `longest common subsequence` between them which will be our answer.

![](../GFG/Attachments/Pasted%20image%2020220615141241.png)

## Code:

```cpp
int lcs(string s1,string s2){
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
int main(){
	string s2 = s1;
	reverse(s2.begin(),s2.end());
	return lcs(s1,s2);
}
```

