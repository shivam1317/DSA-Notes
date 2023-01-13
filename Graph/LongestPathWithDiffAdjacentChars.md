>[!Problem Statement]
>You are given a **tree** (i.e. a connected, undirected graph that has no cycles) **rooted** at node `0` consisting of `n` nodes numbered from `0` to `n - 1`. The tree is represented by a **0-indexed** array `parent` of size `n`, where `parent[i]` is the parent of node `i`. Since node `0` is the root, `parent[0] == -1`.
>You are also given a string `s` of length `n`, where `s[i]` is the character assigned to node `i`.
>Return the length of the **longest path** in the tree such that no pair of **adjacent** nodes on the path have the same character assigned to them.
>[Problem link](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/description/)

## Example:

**Input:** 
```
parent = [-1,0,0,1,1,2], s = "abacbe"
```
**Output:** 
```
3
```
**Explanation:** 

![](../GFG/Attachments/Pasted%20image%2020230113220810.png)

```
The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1 -> 3. The length of this path is 3, so 3 is returned.
It can be proven that there is no longer path that satisfies the conditions.
```

## Approach:

--> So this problem is very similar to `Finding diameter of tree` problem where we find the `longest path from any leaf node to any other leaf node.` So let's first discuss the diameter of tree and then we will see how its useful for this problem.

### Diameter of Tree (Initial idea)

--> To find diameter of tree, we will start from `root` node and recursively we will goto any leaf node in its left or right subtree. 

Consider one tree here:

![](../GFG/Attachments/Pasted%20image%2020230113221532.png)

--> Now for each node we will have 2 possibilities:

1. If that node is the turning point for the path means diameter of tree will pass through this node.

For example in diagram node `A` is passing the first possibility:

![](../GFG/Attachments/Pasted%20image%2020230113221822.png)

then we will find the diameter of left subtree and right subtree and add current node into it and we will get our final diamter.

2. If that node is just contributing to the path which is diameter of tree.
For example in diagram node `A` is passing the second possilibity:

![](../GFG/Attachments/Pasted%20image%2020230113222111.png)

So here we will just find the longest diameter of both of its subtrees and add `1` into it and pass to its parent.

### Actual implementation 

--> Now in this problem also we can see that we need the `longest path` so here we can apply the same logic which we used above but with some changes!

First of all this is not a binary tree, it will be generic tree so it will be easy for us to think it as a graph and to traverse a graph we will need `adjacency list` which we can make from `parent` array.

Making adjacency list:

```cpp
int n = parent.size();
unordered_map<int,vector<int>>adj;
// we are starting from 1st index because parent of root will be -1 and we have already visited this node as we are starting from this node only
for(int i=1;i<n;i++){
	adj[parent[i]].push_back(i);
}
```

Now we will use `dfs` to traverse this graph and during traversing the graph we will follow the same logic which we followed in finding diameter of tree but there will be some edge cases.

### Edge cases:

--> We know that for finding diameter of tree our path will begin and end at any `leaf node` but in this problem, that's not the case so we have to take care of one more case which will be like this:

![](../GFG/Attachments/Pasted%20image%2020230113223402.png)

So to handle this case we will put one condition `If labels of parent and child are same then we will just skip that node and we will traverse current parent's other childs.`

### Approach (Continue...)

--> Now in trees we now that there will be at max only 2 children to any node but here its not the case so we will maintain 2 variables called `bestLength` and `secondBest` which will be the top 2 max answers from all of parent's childs. 

Also for each node we will implement those 2 cases from `diameter of tree` problem.

```
Case 1: Use current node as a turning point for path
Case 2: Use current node as a contributor to final path
```

--> And at last take `maximum` of these 2 cases and store it in global `ans` variable.

```
Remember that we have to return the answer of case 2 because in case 2 we are returning answer to current node's parent.
```

## Final code:

```cpp
int ans;
int dfs(int parent,unordered_map<int,vector<int>>&adj,string &s){
	int bestLength = 0;
	int secondBest = 0;
	for(auto &child:adj[parent]){
		int currBest = dfs(child,adj,s);
		// Different adjacent character case
		if(s[parent] == s[child]){
			continue;
		}
		if(currBest > bestLength){
			secondBest = bestLength;
			bestLength = currBest;
		}
		else if(currBest > secondBest){
			secondBest = currBest;
		}
	}
	// Diameter of tree cases
	// Case 1: Pass through
	int passThrough = 1 + bestLength + secondBest;
	// case 2: Contribute to path
	int contriPath = 1 + bestLength;
	// Take maximum of both cases and store in ans
	ans = max({ans,passThrough,contriPath});
	// Returning answer of case 2
	return contriPath;
}
int longestPath(vector<int>& parent, string s) {
	ans = 0;
	int n = parent.size();
	unordered_map<int,vector<int>>adj;
	for(int i=1;i<n;i++){
		adj[parent[i]].push_back(i);
	}
	dfs(0,adj,s);
	return ans;
}
```

#dfs #tree #dpOnTrees 