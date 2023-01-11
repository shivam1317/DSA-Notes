>[!Problem statement]
>- Given an undirected tree consisting of `n` vertices numbered from `0` to `n-1`, which has some apples in their vertices. You spend 1 second to walk over one edge of the tree. Return the minimum time in seconds you have to spend to collect all apples in the tree, starting at **vertex 0** and coming back to this vertex.
>- The edges of the undirected tree are given in the array `edges`, where `edges[i] = [ai, bi]` means that exists an edge connecting the vertices `ai` and `bi`. Additionally, there is a boolean array `hasApple`, where `hasApple[i] = true` means that vertex `i` has an apple; otherwise, it does not have any apple.

## Example:

**Input:** 
```
n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
```
**Output:** 
```
8
``` 
**Explanation:** 

![](../GFG/Attachments/Pasted%20image%2020230111150054.png)
```
The figure above represents the given tree where red vertices have an apple. One optimal path to collect all apples is shown by the green arrows.
```

## Approach:

--> we can think of this tree as a `undirected graph` where every node is connected with its childrens and parent node. so we will first build a `adjacency list` from `edges` array.

```
To get an apple from one node we will need 2 seconds per node: 1) one second to reach there 2) one second to come back from that node
```

--> Now if we are at any node then we will goto its adjacent nodes and after traversing its whole subtree we will check if we can get any apple in subtree or not.

So there will be 2 conditions here:
1. If we can get any apple in subtree of current node then we will add 2 in total time and return this time.
	- we are adding `2` in time here because we have to go through the current node to reach the subtree of the current node to get apples.
2. If we can't get any apple in subtree of current node then we will return 0

### Edge case:

--> If the root node have apple then we will not add `2` in time because we are initially at root node only.

## Code:

```cpp
int dfs(int i,vector<vector<int>>&adj,vector<bool>&vis,vector<bool>&hasApple){
	vis[i] = true;
	int time = 0;
	// Traversing adjacent nodes of current node
	for(auto it:adj[i]){
		if(!vis[it]){
			time += dfs(it,adj,vis,hasApple);
		}
	}
	// if subtree have apples then add 2 in time also managing the edge case here
	if((hasApple[i] || time > 0) && i != 0){
		time+=2;
	}
	return time;
}
int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
	// adjacency list
	vector<vector<int>>adj(n);
	// building graph
	for(int i=0;i<edges.size();i++){
		adj[edges[i][0]].push_back(edges[i][1]);
		adj[edges[i][1]].push_back(edges[i][0]);
	}
	// visited array to store if node is visited or not
	vector<bool>vis(n,false);
	return dfs(0,adj,vis,hasApple);
}
```

#tree #graph #dfs  