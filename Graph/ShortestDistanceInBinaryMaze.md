## Problem Statement

>Given a **n * m** matrix **grid** where each element can either be **0** or **1**. You need to find the shortest distance between a given source cell to a destination cell. The path can only be created out of a cell if its value is 1. 
If the path is not possible between source cell and destination cell, then return **-1**.

>[!note]
> You can move into an adjacent cell if that adjacent cell is filled with element 1. Two cells are adjacent if they share a side. In other words, you can move in one of the four directions, Up, Down, Left and Right.

## Example

**Input:**
```
grid[][] = {{1, 1, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 1},
            {1, 1, 0, 0},
            {1, 0, 0, 1}}
source = {0, 1}
destination = {2, 2}
```
**Output:**
```
3
```
**Explanation:**
1 **1** 1 1
1 **1** 0 1
1 **1** **1** 1
1 1 0 0
1 0 0 1
```
The highlighted part in the matrix denotes the 
shortest path from source to destination cell.
```

## Approach:

--> Here we have to check every path and we will use `bfs` here to traverse every path. also we have to maintain one `visited` array so that we don't visit the already visited cell again.

--> For each cell we will store 3 things: `i,j and current length` and we can store it as `structure or class`. now whenever we will add new cell in our queue then we will increase the length.

If we reach our destination then we will return current length.

## Code:

```cpp
// Structure for storing info about current cell.
	struct Node
    {
        int i, j, len;
        Node(int x, int y, int l)
        {
            i = x;
            j = y;
            len = l;
        }
    };
    // function to check out of bound conditions.
    bool check(int i,int j,int n,int m){
        if(i<0 || j<0 || i>=n || j>=m){
            return false;
        }
        return true;
    }
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {
        queue<Node>q;
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>>vis(n,vector<int>(m,0));
        // dx and dy arrays for going to all 4 sides.
        vector<int>dx = {1,0,-1,0};
        vector<int>dy = {0,1,0,-1};
        Node start = Node(source.first,source.second,0);
        // adding source cell in queue
        q.push(start);
        while(!q.empty()){
            Node cell = q.front();
            q.pop();
            // If we reach at destination then we will return length.
            if(cell.i == destination.first && cell.j == destination.second){
                return cell.len;
            }
            for(int i=0;i<4;i++){
                int nx = cell.i + dx[i];
                int ny = cell.j + dy[i];
                if(check(nx,ny,n,m) && !vis[nx][ny] && grid[nx][ny] == 1){
                    vis[nx][ny] = 1;
                    Node ok = Node(nx,ny,cell.len+1);
                    q.push(ok);
                }
            }
            
        }
        // If we can't reach at destination
        return -1;
    }
```

#graph #bfs