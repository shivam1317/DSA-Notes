>[!Problem Statement]
>A [Hamiltonian path](https://en.wikipedia.org/wiki/Hamiltonian_path), is a path in an **undirected graph** that visits each vertex exactly once. Given an **undirected graph,** the task is to check if a Hamiltonian path is present in it or not.

## Example

**Input:**
```
N = 4, M = 4
Edges[][]= { {1,2}, {2,3}, {3,4}, {2,4} }
```
**Output:**
```
1 
```
**Explanation:** 
```
There is a hamiltonian path: 
1 -> 2 -> 3 -> 4
```

## Approach:

--> Here we have to find a path which will traverse all the nodes in graph. we will use dfs here and to track the number of visited nodes in one dfs call we will pass `N` as parameter and whenever we will visit any node then we will decrease `N` and if N becomes 0 then we will return true means we can visit all nodes and if can't, then we will return false.

## Final Code:

```cpp
bool dfs(int i,int N,vector<int>&vis,vector<vector<int>>&adj){
		// base case
        if(N == 0){
            return true;
        }
        vis[i] = true;
        for(auto it:adj[i]){
            if(!vis[it]){
                if(dfs(it,N-1,vis,adj)){
                    return true;
                }
            }
            
        }
        // backtracking
        vis[i] = false;
        return false;
    }
    bool check(int N,int M,vector<vector<int>> Edges)
    {
        vector<vector<int>>adj(N+1);
        for(auto it:Edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        vector<int>vis(N+1,0);
        for(int i=1;i<=N;i++){
	        // we are doing N-1 because current node should also mark as visited
            if(dfs(i,N-1,vis,adj)){
                return true;
            }
        }
        return false;
    }
```

#dfs #graph #backtracking 
