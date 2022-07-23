## Problem:

>You are playing a game. At each level of the game, you have to choose one of the roads to go to the next level. Initially, you have h amount of health and m amount of money.  
If you take the first road then your health increases by 3 and money increase by 2. If you take the second road then your health decreases by 5 and money decrease by 10. If you take the third road then health decreases by 20 and money increase by 5.  
You have to tell what is the maximum level you can reach up to under the constraints that in no two consecutive levels you can select the same road twice and once your health or money becomes <= 0 game ends(that level is not counted).

## Example:

**Input:**
```
H=20
M=8
```
**Output:**
```
5
```
**Explanation:**
```
Go like this:- R1(23,10)->R3(3,15)->R1(6,17)->R2(1,7)->R1(4,9)-> game ends as we cannot choose
any more roads.
```

## Approach:

--> the 3 roads looks like this:

![](../GFG/Attachments/Pasted%20image%2020220723155611.png)

--> Here we can clearly see that we will start from `road 1` because that's the only road where the values of `h and m` are increasing.

Now we have taken the road `1` in first level but now we have to choose from road `2 and 3` so which one to choose?

--> so why don't we goto both roads one by one and then take the road which will give us the max ans between these 2 roads.
 
==> So here we have to `try out all possible paths` and that's where we will think about `recursion`.

Also remember that we have to choose from road 2 and 3 only when we will be in `odd level` because if we are at even levels like 0,2,4... then we will ofcourse take `road 1` because the values of h and m are increasing there.

So our recursive part will look like this:

```cpp
	if(cnt%2 == 0){
		return 1 + solve(h+3,m+2,cnt+1,dp);
	}else{
		return 1 + max(solve(h-5,m-10,cnt+1,dp),solve(h-20,m+5,cnt+1,dp));
	}
```

Here `cnt` is number of level.

## Base condition:

--> It's stated in question that if `h or m becomes 0 or less than 0` then we have to stop. so that's our base condition.

```cpp
if(h<=0 || m<=0){
	return -1;
}
```

Now we are returning -1 because we don't want to count this level so that's why we will subtract 1 from the level from where the values of h or m became less than or equal to 0.

## Recursive code:

```cpp
int solve(int h,int m,int cnt){
	if(h<=0 || m<=0){
		return -1;
	}
	if(cnt%2 == 0){
		return 1 + solve(h+3,m+2,cnt+1);
	}else{
		return 1 + max(solve(h-5,m-10,cnt+1),solve(h-20,m+5,cnt+1));
	}
}
```

--> But we can convert this code in `DP` using memoization.

the parameters of dp array will be `h and m` because that's the only values which are changing and the size of dp array will be `2001`(From constrains)

## DP solution:

```cpp
int solve(int h,int m,int cnt,vector<vector<int>>&dp){
	if(h<=0 || m<=0){
		return -1;
	}
	if(dp[h][m] != -1){
		return dp[h][m];
	}
	if(cnt%2 == 0){
		dp[h][m] =  1 + solve(h+3,m+2,cnt+1,dp);
	}else{
		dp[h][m] =  1 + max(solve(h-5,m-10,cnt+1,dp),solve(h-20,m+5,cnt+1,dp));
	}
}
int maxLevel(int h,int m)
{
	vector<vector<int>>dp(2001,vector<int>(2001,-1));
	return solve(h,m,0,dp);
}
```

