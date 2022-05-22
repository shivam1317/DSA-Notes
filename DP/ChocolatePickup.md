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

