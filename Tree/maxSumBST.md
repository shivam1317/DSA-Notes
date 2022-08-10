## Problem:

>Given a **binary tree** `root`, return _the maximum sum of all keys of **any** sub-tree which is also a Binary Search Tree (BST)_.

>Assume a BST is defined as follows:
>-   The left subtree of a node contains only nodes with keys **less than** the node's key.
>-   The right subtree of a node contains only nodes with keys **greater than** the node's key.
>-   Both the left and right subtrees must also be binary search trees.

[Problem link](https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/)

## Example:

**Input:** 
```
root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
```
**Output:** 
```
20
```
**Explanation:** 
```
Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
```

![](../GFG/Attachments/Pasted%20image%2020220810165236.png)

## Approach:

--> we will start from `leaf nodes` and for any node we will first find answer for it's children means it's `left and right nodes` so for that we need a traversal technique which will first find answer for left and right and then for root. so this traversal is `Post order(left -> right -> root)`.

Now we know 2 things till now:

```
1. we will start from leaf nodes
2. we will use postorder
```

==> Now first we have to check if any subtree is valid BST or not and for that any node have to satisfy these 2 conditions:

```
1. Current node's value must be greater than maximum value in it's left subtree
2. Current node's value must be smaller than minimum value in it's right subtree
```

--> Now for each node we will store 4 things:

```
1. If it's subtree(Including that node itself) is BST or not
2. Max sum till now
3. minimum value in that tree
4. maximum value in that tree
```

--> Now the question is how we can store these values?

So we can use `pair` or we can use `Class` or `struct` so store these 4 values for each node.

The class will look like this:

```cpp
class Info {
    public:
        int ms; // maximum sum till now
        int mini; // minimum value in tree
        int maxi; // maximum value in tree
        bool isbst; // true if current tree is bst or false.
        // default values
        Info(){
            ms = 0;
            mini = INT_MAX;
            maxi = INT_MIN;
            isbst = true;
        }
};
```

Now for each node, we will first find answers for it's left and right subtree (In postorder manner).

```cpp
Info node;
Info nodeleft = solve(root->left);
Info noderight = solve(root->right);
```

Now we have answers for it's left and right subtree now we just have to check if `The subtree is BST including the current node` and we already know the conditions:

```
1. nodeleft.isbst must be true
2. noderight.isbst must be true
3. the max value of leftsubtree i.e. nodeleft.maxi must be lower than root->val
4. the min value of rightsubtree i.e. noderight.mini must be greater than root->val
```

If it satisfies all 4 conditions then we know that `it's a BST`. so we will add `root->val` in `nodeleft.ms + noderight.ms` which will be total sum of this tree.

- `node.mini` will be minimum value of `root->val` and `nodeleft.mini`
- `node.maxi` will be maximum value of `root->val` and `noderight.maxi`

Let's see this part in code:

```cpp
if(nodeleft.isbst && noderight.isbst && root->val > nodeleft.maxi && root->val < noderight.mini){
	node.isbst = true;
	node.ms = root->val + nodeleft.ms + noderight.ms;
	node.mini = min(root->val,nodeleft.mini);
	node.maxi = max(root->val,noderight.maxi);
}
```

--> Now if the above conditions is false then we will mark `node.isbst` as false but `node.ms` will be maximum of `nodeleft.ms and noderight.ms` because we might found any answer in any one of the subtree so we will not reset it.

```cpp
else{
	node.isbst = false;
	node.ms = max(nodeleft.ms,noderight.ms);
}
```

>Remember that node.mini and node.maxi will not be changed in this case so it will have the default values which are INT_MAX and INT_MIN.

--> At last maintain one global variable `ans` which will be our final answer and modify our ans and return `node`.

```cpp
ans = max(ans,node.ms);
return node;
```

--> So now let's see the full code:

## Final Code:

```cpp
class Info {
    public:
        int ms;
        int mini;
        int maxi;
        bool isbst;
        Info(){
            ms = 0;
            mini = INT_MAX;
            maxi = INT_MIN;
            isbst = true;
        }
};
class Solution {
public:
    int ans = 0;
    Info solve(TreeNode* root){
        if(root == NULL){
            return Info();
        }      
        Info node;
        Info nodeleft = solve(root->left);
        Info noderight = solve(root->right);
        if(nodeleft.isbst && noderight.isbst && root->val > nodeleft.maxi && root->val < noderight.mini){
            node.isbst = true;
            node.ms = root->val + nodeleft.ms + noderight.ms;
            node.mini = min(root->val,nodeleft.mini);
            node.maxi = max(root->val,noderight.maxi);
        }
        else{
            node.isbst = false;
            node.ms = max(nodeleft.ms,noderight.ms);
        }
        ans = max(ans,node.ms);
        return node;
    }
    int maxSumBST(TreeNode* root) {
        solve(root);
        return ans;
    }
```