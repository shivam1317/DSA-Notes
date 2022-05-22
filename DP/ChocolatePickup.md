## Problem:

>Ninja has a 'GRID' of size 'R' X 'C'. Each cell of the grid contains some chocolates. Ninja has two friends Alice and Bob, and he wants to collect as many chocolates as possible with the help of his friends.
>Initially, Alice is in the top-left position i.e. (0, 0), and Bob is in the top-right place i.e. (0, ‘C’ - 1) in the grid. Each of them can move from their current cell to the cells just below them. When anyone passes from any cell, he will pick all chocolates in it, and then the number of chocolates in that cell will become zero. If both stay in the same cell, only one of them will pick the chocolates in it.
>If Alice or Bob is at (i, j) then they can move to (i + 1, j), (i + 1, j - 1) or (i + 1, j + 1). They will always stay inside the ‘GRID’.
>Your task is to find the maximum number of chocolates Ninja can collect with the help of his friends by following the above rules.

## Example:

```
Input: ‘R’ = 3, ‘C’ = 4
       ‘GRID’ = [[2, 3, 1, 2], [3, 4, 2, 2], [5, 6, 3, 5]]
Output: 21

Initially Alice is at the position (0,0) he can follow the path (0,0) -> (1,1) -> (2,1) and will collect 2 + 4 + 6 = 12 chocolates.

Initially Bob is at the position (0, 3) and he can follow the path (0, 3) -> (1,3) -> (2, 3) and will colllect 2 + 2 + 5 = 9 chocolates.

Hence the total number of chocolates collected will be 12 + 9 = 21. there is no other possible way to collect a greater number of chocolates than 21.
```

--> Diagram for this example:

![](Attachments/Pasted%20image%2020220522002249.png)

## Approach:

--> Here we can see that we have fixed starting point and not fixed ending point. so we will start our recursion from fixed starting point.

Here we will maintain 2 variables `(i1,j1)` and `(i2,j2)` for Alice and Bob's movement. And we are sure that `they will reach the destination at the same time`

--> Here instead of taking `i1` and `i2` we can take them as single `i` because the row is not changing for both, only column is changing so we will take `i` as common row for both alice and bob.

## Base case:

--> There are 2 type of base cases:

1. When we reach destination
2. Out of bount cases when we goto outside grid

--> if we reach out of bound case then we will simply return `-1e8` 

```cpp
if(j1 < 0 || j1 >= m || j2 < 0 || j2 >= m){
	return -1e8;
}
```

--> When we reach destination

Now here we have to consider 2 things:

1. If alice and bob both reaches at the same point then we will take the element only once
2. If both reaches at differnt point then we will take the sum of both elements.

```cpp
if(i == n-1){
	if(j1 == j2){
		return arr[i][j1];
	}
	return arr[i][j1] + arr[i][j2];
}
```

## Recursive Code:

--> Now we will move alice and bob simultaneously so that means they will move together in the grid. So for `Alice's` one movement there are 3 movement of bob:
1. left diagonal
2. down
3. right diagonal

And also alice have 3 movements as same as bob so total movements will be `9`

we can write it like this:

```cpp
for(int d1=-1;d1<=1;d1++){
	for(int d2=-1;d2<=1;d2++){
		// i will be same for both and both will go down
		solve(i+1,j1+d1,j2+d2);
	}
}
```

--> Now if alice and bob both are at same cell then we will consider the cell value only once otherwise we will take sum of both `a[i][j1]` and `a[i][j2]`

```cpp
int maxi = 0;
for(int d1=-1;d1<=1;d1++){
	for(int d2=-1;d2<=1;d2++){
		if(j1 == j2){
			maxi = max(maxi,arr[i][j1] + solve(i+1,j1+d1,j2+d2));
		}else{
			maxi = max(maxi,arr[i][j1] + arr[i][j2] + solve(i+1,j1+d1,j2+d2));
		}
	}
}
return maxi;
```

## Complexity:

```
Time complexity: O(3^n * 3^n)
Space complexity: O(n)
```

## Memoization

--> Here we will make 3D matrix of `NxMxM` called `dp[N][M][M]`

Code will look like this:

```cpp
int solve(int i,int j1,int j2,vector<vector<int>>&arr,vector<vector<vector<int>>>&dp){

	if(j1 < 0 || j1 >= m || j2 < 0 || j2 >= m){
		return -1e8;
	}
	if(i == n-1){
		if(j1 == j2){
			return arr[i][j1];
		}
		return arr[i][j1] + arr[i][j2];
	}
	if(dp[i][j1][j2] != -1){
		return dp[i][j1][j2];
	}
	int maxi = 0;
	for(int d1=-1;d1<=1;d1++){
		for(int d2=-1;d2<=1;d2++){
			if(j1 == j2){
				maxi = max(maxi,arr[i][j1] + solve(i+1,j1+d1,j2+d2,arr,dp));
			}else{
				maxi = max(maxi,arr[i][j1] + arr[i][j2] + solve(i+1,j1+d1,j2+d2,arr,dp));
			}
		}
	}
	return dp[i][j1][j2] = maxi;
}

int main(){
	vector<vector<vector<int>>>dp(N,vector<vector<int>>(M,vector<int>(M,-1)));
	solve(0,0,m-1);
}
```

## Complexity:

```
Time complexity: O(NxMxM)*9
Space complexity: O(NxMxM) + O(N)
```

## Tabulation Code

--> In tabulation, we will start from last row and go till `0`

So if we are at n-1th row then alice and bob can finish at any cell and also they can finish at same cell too so we have to write base case like this:

```cpp
// Base case
for(int j1=0;j1<m;j1++){
	for(int j2=0;j2<m;j2++){
		if(j1 == j2){
			dp[n-1][j1][j2] = arr[n-1][j1];
		}
		else{
			dp[n-1][j1][j2] = arr[n-1][j1] + arr[n-1][j2];
		}
	}
}
```

--> Now i will run from `n-2 to 0` and j1 and j2 run from `0 to m-1`

```cpp
for(int i=n-2;i>=0;i--){
	for(int j1=0;j1<m;j1++){
		for(int j2=0;j2<m;j2++){
			int maxi = -1e8;
			for(int d1=-1;d1<=1;d1++){
				for(int d2=-1;d2<=1;d2++){
					int value = 0;
					if(j1 == j2){
						value = arr[i][j1];
					}else{
						maxi = arr[i][j1] + arr[i][j2];
					}
					if(j1+d1 >= 0 && j1+d1 < m && j2+d2>=0 && j2+d2 < m){
						value += dp[i+1][j1+d1][j2+d2];
					}else{
						value += -1e8;
					}
					maxi = max(maxi,value);
				}
			}
			dp[i][j1][j2] = maxi;
		}
	}
}
return dp[0][0][m-1];
```

## Space optimisation :

--> Here we will use a 2D `curr` and `prev` array instead of storing whole matrix in DP array.

```cpp
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    vector<vector<int>>prev(c,vector<int>(c));
	vector<vector<int>>curr(c,vector<int>(c));
	for(int j1=0;j1<c;j1++){
		for(int j2=0;j2<c;j2++){
			if(j1 == j2){
				prev[j1][j2] = grid[r-1][j1];
			}
			else{
				prev[j1][j2] = grid[r-1][j1] + grid[r-1][j2];
			}
		}
	}
	for(int i=r-2;i>=0;i--){
		for(int j1=0;j1<c;j1++){
			for(int j2=0;j2<c;j2++){
				int maxi = -1e8;
				for(int d1 = -1;d1<=1;d1++){
					for(int d2=-1;d2<=1;d2++){
						int value = 0;
						if(j1 == j2){
							value = grid[i][j1];
						}else{
							value = grid[i][j1] + grid[i][j2];
						}
						if(j1+d1 >= 0 && j1+d1 < c && j2+d2 >= 0 && j2+d2 < c){
							value += prev[j1+d1][j2+d2];
						}
						maxi = max(maxi,value);
					}
				}
				curr[j1][j2] = maxi;
			}
		}
		prev = curr;
	}
	return prev[0][c-1];
}
```

