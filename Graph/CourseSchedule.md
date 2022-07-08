## Problem:

> There are a total of **n** tasks you have to pick, labeled from 0 to n-1. Some tasks may have **prerequisites** tasks, for example to pick task 0 you have to first finish tasks 1, which is expressed as a pair: [0, 1]  
> Given the total number of **n** tasks and a list of prerequisite pairs of size **m**. Find a ordering of tasks you should pick to finish all tasks.  
> **Note:** There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all tasks, return an empty array. Returning any correct order will give the output as **1**, whereas any invalid order will give the output **0.**

## Example:

**Input:**

```
n = 2, m = 1
prerequisites = {{1, 0}}
```

**Output:**

```
1
```

**Explanation:**

```
The output 1 denotes that the order is valid. So, if you have, implemented your function correctly, then output would be 1 for all test cases.
One possible order is [0, 1].
```

## Approach

--> Now if we make a graph for this question then it will look like this:

![](../GFG/ttachments/Pasted%20image%2020220523144615.png)

So here if we `transpose` the graph then we will get `0` first because we will start with `0` and it can be our ans. So here we just have to find `toposort for directed graph` which we can do using `bfs` and `dfs` but we will do it using `bfs` here.

--> To find toposort, we will use `kahn's algorithm` in which we find the `indegree` for vertexes and if indegree is `0` then we add them in our queue.

--> Also we have to return empty array if doing all tasks is not possible. so we will make one `count` variable which will be incremented in each while loop till queue become empty so if toposort traverses all the elements then the queue will contain `n` elements and after all while loops count will be `n` so

if count is equal to `n` then we will return our ans else we will return empty array.

```cpp
vector<vector<int>>make_graph(int n,int m,vector<vector<int>>&prerequisites){
        vector<vector<int>>adj(n);
        for(int i=0;i<m;i++){
			// Making directed graph
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        return adj;
    }
    vector<int> findOrder(int n, int m, vector<vector<int>> prerequisites)
    {
       vector<vector<int>> adj = make_graph(n,m,prerequisites);
      vector<int>ans;
      vector<int>indegree(n,0);
      for(int i=0;i<n;i++){
          for(auto it:adj[i]){
              indegree[it]++;
          }
      }
      queue<int>q;
		// If at starting any node have indegree 0 then add it in queue
      for(int i=0;i<n;i++){
          if(indegree[i] == 0){
              q.push(i);
          }
      }
      int count = 0;
      while(!q.empty()){
          int node = q.front();
          q.pop();
		  // Add the node into ans after popping from queue
          ans.push_back(node);
          for(auto it:adj[node]){
              indegree[it]--;
			  // If indegree becomes 0 then add that node in queue
              if(indegree[it] == 0){
                  q.push(it);
              }
          }
          count++;
      }
      return count == n ? ans : vector<int>{};
    }
```
