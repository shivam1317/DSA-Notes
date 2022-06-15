## problem:

>Given two strings, ‘A’ and ‘B’. Return the shortest supersequence string ‘S’, containing both ‘A’ and ‘B’ as its subsequences. If there are multiple answers, return any of them.
Note: A string 's' is a subsequence of string 't' if deleting some number of characters from 't' (possibly 0) results in the string 's'.

## Example:

```
Suppose ‘A’ = “brute”, and ‘B’ = “groot”

The shortest supersequence will be “bgruoote”. As shown below, it contains both ‘A’ and ‘B’ as subsequences.

A   A A     A A
b g r u o o t e
  B B   B B B  

It can be proved that the length of supersequence for this input cannot be less than 8. So the output will be bgruoote.
```

## Approach:

==> To get the length of shortest common supersequence, we just have to `take the common characters only once and take every other character` so our final answer will be:

```
n+m-len(longestCommonSubsequence)
```

## Printing the Shortest Common Supersequence 

--> To print the supersequence, first let's make lcs matrix for these 2 strings.

lcs matrix for `brute` and `groot` will look like this:

![](../GFG/Attachments/Pasted%20image%2020220615185145.png)

--> Now if we start from end of the matrix which is `NxM` and then go till 0th index or 0th row using these 2 conditions:

```
1. if s1[i] and s2[j] are same then add that character only once and goto upper diagonal means dp[i-1][j-1]
2. if s1[i] and s2[j] are not same then take the maximum of dp[i-1][j] and dp[i][j-1] and goto that direction. But if both are same then you can goto any direction. The main thing to remember here is that add the character which was not considered during moving i.e. if we are moving to dp[i-1][j] then take character on dp[i][j-1] (means s2[j-1]) and if we are moving to dp[i][j-1] then take character on dp[i-1][j] (means s1[i-1]) in our answer string.
```

--> The below diagram will show this process:

>The green path is the path which we are following. and the numbers before each character defines the sequence of getting added in answer string.

![](../GFG/Attachments/Pasted%20image%2020220615202915.png)

--> After getting the string we will just reverse it and it will be our answer.

## Code:

```cpp
string solve(string s1,string s2){
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
    int i=s1.size(),j=s2.size();
    string ans = "";
    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){
            ans += s1[i-1];
            i--;
            j--;
        }else if(dp[i-1][j] > dp[i][j-1]){
			// If we are going upper then we will take the current element in answer string
            ans += s1[i-1];
            i--;
        }else{
            ans += s2[j-1];
            j--;
        }
    }
	// Now in the above while loop we have written (i>0 && j>0) so it means if any of them becomes 0 then that loop will break so we have to take the other elements in our ans string also because suppose if we break at i=0 and j is still 3 then we have to add that 3 elements in our answer string that's why we are running these 2 separte for loops.
    while(i>0){
        ans += s1[i-1];
        i--;
    }
    while(j>0){
        ans += s2[j-1];
        j--;
    }
	// reverse the ans string and return it
    reverse(ans.begin(),ans.end());
    return ans;
}
```