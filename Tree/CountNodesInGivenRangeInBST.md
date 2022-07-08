## Problem:

> Given a Binary Search Tree (BST) and a range **l-h(inclusive)**, count the number of nodes in the BST that lie in the given range.

    -   The values smaller than root go to the left side
    -   The values greater and equal to the root go to the right side

## Example:

**Input:**

```
      10
     /  \
    5    50
   /    /  \
  1    40  100
l = 5, h = 45
```

**Output:**

```
3
```

**Explanation:**

```
5 10 40 are the node in the range
```

## Diagram for above example:

![](../GFG/Attachments/Pasted%20image%2020220705140337.png)

## Approach:

--> we know in BST that `all left subtree contains element smaller than current element and all right subtree elements are bigger than current element`. So by using this logic we will traverse the tree in 3 conditions :

```
1. If the current node is in range then we will make call for both left and right subtree
2. If the current node is not in range but is greater than l but not lesser than h then we will goto left subtree because we will find all bigger elements if we go right then we will find all elements bigger than h but we want smaller elements than h.
3. If the current node is not in range but is not greater than l then we will goto right subtree because we will find bigger elements which are greater than l and that's what we want.
```

## base condition:

If current node will become NULL then we will return 0.

## Code:

```cpp
	int solve(Node *root,int l,int h){
		// base condition
        if(root == NULL){
            return 0;
        }
		// If current node is in range
        if(root->data >= l && root->data <= h){
			// adding 1 for current element
            return 1 + solve(root->left,l,h) + solve(root->right,l,h);

        }else if(root->data >= l){
            return solve(root->left,l,h);
        }else{
            return solve(root->right,l,h);
        }
    }
    int getCount(Node *root, int l, int h)
    {
        return solve(root,l,h);
    }
```
