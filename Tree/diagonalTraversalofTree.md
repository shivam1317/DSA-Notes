## Problem:

> Given a Binary Tree, print the **diagonal traversal** of the binary tree.
> Consider lines of slope -1 passing between nodes. Given a Binary Tree, print all diagonal elements in a binary tree belonging to same line.

## Example:

**Input** :

```
            8
         /     \
        3      10
      /   \      \
     1     6     14
         /   \   /
        4     7 13
```

**Output** :

```
8 10 14 3 6 7 13 1 4
```

Explaination:

![](../GFG/Attachments/Pasted%20image%2020220706140122.png)

## Approach:

--> So here from diagram we are going diagonally in the right side so we will traverse each node in the way that `we will take only right node of current node in one diagonal` and if we goto it's left then it will be another diagonal. and like that we will go recursively and traverse whole tree.

So to store the nodes we will use map which will have one vector as values. and we will use simple numbers like `0,1,2..` as current slope. and we will store all the nodes in ith slope in the map of vector for ith key. and at last we will add all elements of map in ans vector.

![](../GFG/Attachments/Pasted%20image%2020220706145121.png)

## Code:

```cpp
void solve(Node *root,int currSlope,map<int,vector<int>>&mp){
    if(root == NULL){
        return;
    }
	// add current node in current slope's value vector
    mp[currSlope].push_back(root->data);
	// goto left but increase the slope because it's gonna be in next slope
    solve(root->left,currSlope+1,mp);
	// goto right node but don't change slope because all right values are in same slope
    solve(root->right,currSlope,mp);
}
vector<int> diagonal(Node *root)
{
   map<int,vector<int>>mp;
   solve(root,0,mp);
   vector<int>ans;
	// add the map values in answer vector.
   for(auto it:mp){
       for(auto x:it.second){
           ans.push_back(x);
       }
   }
   return ans;
}
```