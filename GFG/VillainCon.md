## Problem:

>The minions are very elitist in nature. If minion x admires minion y, then y thinks too highly of himself and does not admire x back. Also, if x admires y, x also admires everyone that y admires.  
All the minions are going to be present at the Villain Con. They want to make sure that they do not dress in the same color as someone who admires them.   
There are **N** minions and **M** relations between them. The relations are given in a 2D array **mat**. Each relation is given in xi , yi format where yi admires xi. Find the minimum number of different colours that the minions will be dressing in.

## Example:

**Input:** 
```
N = 5, M = 6
mat = {{1, 3}, 
       {2, 3}, 
       {3, 4}, 
       {1, 4}, 
       {2, 5}, 
       {3, 5}}
```

**Output:** 
```
3
```
**Explaination:**
```
If we assign red colour to 1 and 2, green colour to 3, and blue colour to 4 and 5, then every minion will have different coloured dresses from the one who admires them.
```

**Diagram:**

![](Attachments/Pasted%20image%2020220604144017.png)

## Approach:

--> Now if we inverse the graph then we can analyse that the node with indegree 0 is the last node which is not admiring anyone.

Inverted graph with indegrees of each node:

![](Attachments/Pasted%20image%2020220604144148.png)

So from the graph we can see that `1 and 2 have indegree 0` so we can start `BFS` from that node and `find the maximum depth of graph` which will be our answer.

--> So here we can find toposort using `Kahn's Algorithm` and also we will use indegree array in that.

And at last we will return our ans.

## Code:

```cpp
int minColour(int N, int M, vector<int> mat[]) {
        vector<vector<int>>adj(N+1);
        vector<int>indegree(N+1,0);
        for(int i=0;i<M;i++){
            adj[mat[i][0]].push_back(mat[i][1]);
            indegree[mat[i][1]]++;
        }
        queue<int>q;
        int ans = 0;
        for(int i=1;i<=N;i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int size = q.size();
			// We are running this for loop because we don't want to increase the ans for nodes in same level
            for(int k=0;k<size;k++){
                int node = q.front();
                q.pop();
                for(auto it:adj[node]){
                    indegree[it]--;
                    if(indegree[it] == 0){
                        q.push(it);
                    }
                }
            }
            
            ans++;
        }
        return ans;
    }
```
