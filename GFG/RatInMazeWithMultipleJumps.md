## Problem:

>A Maze is given as **n*n** matrix of blocks where source block is the upper left most block i.e., **matrix[0][0]** and destination block is lower rightmost block i.e., **matrix[n-1][n-1]**. A rat starts from source and has to reach the destination. The rat can move in only two directions: first forward if possible or down. If multiple solutions exist, the shortest earliest hop will be accepted. For the same hop distance at any point, forward will be preferred over downward. In the maze matrix, 0 means the block is the dead end and non-zero number means the block can be used in the path from source to destination. The non-zero value of mat[i][j] indicates number of maximum jumps rat can make from cell mat[i][j]. In this variation, Rat is allowed to jump multiple steps at a time instead of 1. Find a matrix which describes the position the rat to reach at the destination.

## Example:

**Input:** 
```
{{2,1,0,0},{3,0,0,1},{0,1,0,1},{0,0,0,1}}
```
**Output:** 
```
{{1,0,0,0},{1,0,0,1},{0,0,0,1},{0,0,0,1}}
```
**Explanation:** 
```
Rat started with matrix[0][0] and can jump up to 2 steps right/down. First check 
matrix[0][1] as it is 1, next check matrix[0][2] ,this won't lead to the solution. 
Then check matrix[1][0], as this is 3(non-zero),so we can make 3 jumps to reach matrix[1][3]. 
From matrix[1][3] we can move downwards taking 1 jump each time to reach destination at 
matrix[3][3].
```

**Diagram**

![](Attachments/Pasted%20image%2020220602140622.png)

## Approach:

--> Here we will start from `arr[0][0]` and we will first goto forward because in question it's states that `forward will be preferred over downward.` so we will try every jump in the loop of `1 to arr[i][j]` because at max we can take arr[i][j] so we will check if we can reach `arr[n-1][n-1]` by taking any path and if we don't reach end then we will again make it `0` by doing backtracking. and if we reach end of matrix then we will make it `1` and return `true`

--> Also we will make one `isSafe` function will whill ensure that we don't get outside of matrix by checking out of bound conditions and also we will check if current cell is `0` is not because if it's 0 then we can't go forward.

The helper function code will look like this:

```cpp
bool isSafe(int n,int x,int y,vector<vector<int>>&arr){
	if(x >= n || y>=n || arr[i][j] == 0){
		return false;
	}
	return true;
}
```

--> Now we will go recursive and in every recursion call we will first check if it's safe and if it's safe then we will mark that position in our ans matrix as `1` and then we will run a for loop of `1 to arr[i][j]` and check if it gives `true` then we will return true else we will go down.
Also after leaving for loop we will again make it `0` as backtracking.

## Base case

--> If we will reach `arr[n-1][n-1]` then we will make it `1` in our ans matrix and return true.

```cpp
if(x == n-1 && y == n-1){
	ans[x][y] = 1;
	return true;
}
```

## Code:

```cpp
 bool isSafe(int n,int x,int y,vector<vector<int>>&matrix){
        if(x >= n || y >= n || matrix[x][y] == 0){
            return false;
        }
        return true;
    }
    bool solve(int n,int x,int y,vector<vector<int>>&ans,vector<vector<int>>&matrix){
        // Base case
        if(x == n-1 && y == n-1){
            ans[x][y] = 1;
            return true;
        }
		// If the current cell is safe then only we will run this loop
        if(isSafe(n,x,y,matrix)){
			// Marking current cell as 1 in ans matrix
            ans[x][y] = 1;
            for(int i=1;i<=matrix[x][y] && i < n;i++){
                // Going forward
                if(solve(n,x,y+i,ans,matrix)){
                    return true;
                }
                // Going down
                if(solve(n,x+i,y,ans,matrix)){
                    return true;
                }
            }
			// Making current cell as 0 for backtracking
            ans[x][y] = 0;
            return false;
        }
        return false;
    }
	vector<vector<int>> ShortestDistance(vector<vector<int>>&matrix){
	   int n = matrix.size();
	   if(matrix[0][0] == 0 && n != 1){
	       return {{-1}};
	   }
	   vector<vector<int>>ans(n,vector<int>(n,0));
	   solve(n,0,0,ans,matrix);
	   return ans;
	}
```