## Problem:

>Given a directed acyclic graph(DAG) with n nodes labeled from 0 to n-1. Given edges, s and d ,count the number of ways to reach from s to d.There is a directed Edge from vertex edges[i][0] to the vertex edges[i][1].


## Example:

**Input:** 
```
edges = {{0,1},{0,3},{1,2},{3,2}}, 
n = 4, s = 0, d = 2
```
**Output:** 
```
2
```
**Explanation:** 
```
There are two ways to reach at 2 from 0. These are-
1. 0->1->2
2. 0->3->2
```

## Approach:

--> Here from question we can see that it's graph problem and we have to find all possible paths for reaching from one node to other.

So first we will create one adjacency list from the `edges` vector and then we will apply `DFS` to traverse the nodes and if we reach `d` node then we will increase the count variable.

## Code:

```cpp
int count = 0;
    void dfs(vector<vector<int>>&adj,int n,int node,int d){
        if(node == d){
            count++;
            return;
        }
        for(auto x:adj[node]){
            dfs(adj,n,x,d);
        }
    } 
	int possible_paths(vector<vector<int>>edges, int n, int s, int d){
	    vector<vector<int>>adj(n+1);
	    for(int i=0;i<edges.size();i++){
	        adj[edges[i][0]].push_back(edges[i][1]);
	    }
	    dfs(adj,n,s,d);
	    return count;
	}
```

