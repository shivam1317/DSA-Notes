## problem statement:

>The cost of stock on each day is given in an array **A**[] of size **N**. Find all the segment of days on which you buy and sell the stock so that in between those days your profit is maximum.  
**Note:** Since there can be multiple solutions, the driver code will return 1 if your answer is correct, otherwise, it will return 0. In case there's no profit the driver code will return the string "**No Profit**" for a correct solution.

## Example:

**Input:**
```
N = 7
A[] = {100,180,260,310,40,535,695}
```
**Output:**
```
1
```
**Explanation:**
```
One possible solution is (0 3) (4 6)
We can buy stock on day 0,
and sell it on 3rd day, which will 
give us maximum profit. Now, we buy 
stock on day 4 and sell it on day 6.
```

## Approach:

--> here we can buy and sell stock as many times as we want but there are certain conditions:

```
1. you must have to sell a already bought stock before buying a new one
2. you can't buy 2 stocks continuosly means if you already have a stock then you can just sell it.
```

So here we will need 2 things: 

```
1. a index of element which will traverse the array
2. a buy variable which will tell us whether we can buy this stock or not and it will be boolean so if buy is 1 then we can buy otherwise we can't buy it.
```

Now for each element if `buy` is true means we can buy then we have 2 conditions:

```
1. We buy it 
2. we don't buy it
```

and this scenario is similar to pick and not pick method. so let's see both conditions

1. If we buy it:
then we will add current price in profit (but in negative because we have bought it with our money) and we will make a call for i+1 with buy as 0 because now we can't buy any stock

```cpp
-prices[i] + solve(i+1,false);
```

2. if we don't buy it:

then we will not add anything in profit and just make a call for i+1 and keep buy as it is.

```cpp
0 + solve(i+1,true);
```

and at last we will take maximum of these 2 conditions.

--> Now let's see if buy is false.

then also we have 2 conditions:

```
1. we sell the stock with current element as profit
2. we don't sell it
```

1. If we sell it
then we will add current price as profit and we will make `buy` as true means now we can buy a stock and also we will make a call for i+1.

```cpp
price[i] + solve(i+1,1);
```

2. If we don't sell it
then we will simply make a call for i+1 and keep buy variable as it is.

```cpp
0 + solve(i+1,0);
```

and at last we will add maximum of these 2 conditions in profit.

## base case:

If we reach at end of the array then we will have to check whether we are holding any stock or not so if i becomes `n` then we will return 0 so that the profit will become negative if we are still holding a stock and it will not be considered.

```cpp
if(i == n){
	return 0;
}
```

## Recursive code:

```cpp
int solve(int i,bool buy,vector<int>&price){
	// base case
	if(i == n){
		return 0;
	}
	// if we can buy
	if(buy){
		profit = max(-price[i] + solve(i+1,0),solve(i+1,1));
	}
	// if we can't buy
	else{
		profit = max(price[i] + solve(i+1,1),solve(i+1,0));
	}
	return profit;
}
```

```
Time complexity: 2^n
Space complexity: O(N)
```

## Memoization

```cpp
int solve(int i,bool buy,vector<int>&price,vector<vector<int>>&dp){
	// base case
	if(i == n){
		return 0;
	}
	if(dp[i][buy] != -1){
		return dp[i][buy];
	}
	// if we can buy
	if(buy){
		profit = max(-price[i] + solve(i+1,0),solve(i+1,1));
	}
	// if we can't buy
	else{
		profit = max(price[i] + solve(i+1,1),solve(i+1,0));
	}
	return dp[i][buy] = profit;
}
int main(){
	vector<vector<int>>dp(n,vector<int>(2,-1));
	return solve(0,1,price,dp);
}
```

```
Time complexity: O(Nx2)
Space complexity: O(Nx2) + O(N)
```

## Tabulation

here we will just make dp array of size `n+1x2` and we will initialise `dp[n][0]` and `dp[n][1]` as 1 as base case.

```cpp
long getMaximumProfit(long *values, int n)
{
    vector<vector<long>>dp(n+1,vector<long>(2,0));
    dp[n][0] = dp[n][1] = 0;
    for(int i=n-1;i>=0;i--){
        for(int buy=0;buy<=1;buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[i]+dp[i+1][0],dp[i+1][1]);
            }else{
                profit = max(values[i]+dp[i+1][1],dp[i+1][0]);
            }
            dp[i][buy] = profit;
         }
    }
    return dp[0][1];
}
```

## Space optimisation:

```cpp
long getMaximumProfit(long *values, int n)
{
    vector<long>ahead(2,0),curr(2,0);
    ahead[0] = ahead[1] = 0;
    for(int i=n-1;i>=0;i--){
        for(int buy=0;buy<=1;buy++){
            long profit = 0;
            if(buy){
                profit = max(-values[i]+ahead[0],ahead[1]);
            }else{
                profit = max(values[i]+ahead[1],ahead[0]);
            }
            curr[buy] = profit;
         }
        ahead = curr;
    }
    return ahead[1];
}
```

Now instead of making an array of size 2 we can use `4` variables and solve it but it will take same time complexity.

```cpp
long getMaximumProfit(long *values, int n)
{
    long aheadNotBuy,aheadBuy,currNotBuy,currBuy;
    aheadNotBuy = aheadBuy = 0;
    for(int i=n-1;i>=0;i--){
		currBuy =  max(-values[i]+aheadNotBuy,aheadBuy);
		currNotBuy = max(values[i]+aheadBuy,aheadNotBuy);
        aheadNotBuy = currNotBuy;
        aheadBuy = currBuy;
    }
    return aheadBuy;
}
```

```
Time complexity: O(n)
Space complexity: O(1)
```

