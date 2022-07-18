## Problem:

>Given a BST and a number **X**, find **Ceil of X**.  
**Note:** Ceil(X) is a number that is either equal to X or is immediately greater than X.

## Example:

**Input:**      
```
	  5
    /   \
   1     7
    \
     2 
      \
       3
X = 3
```
**Output:** 
```
3
```

**Explanation:** 
```
We find 3 in BST, so ceil
of 3 is 3.
```

## Approach:

--> we know that in BST `the values in left subtree will be less than current node and the values in right subtree will be greater than the current node`. so here we have to find the ceil value for the given `input`.

==> So first we will start from the root node and check if it's greater than or less than the target. if it's greater than or equal to `input` then we will store it as valid ans and goto `left side` because we want the closest max value to `input` and we know that if we go right side then we will get all greater values.
 
--> If `input is greater than current node's value then we will goto right side` to find greater values.

![](../GFG/Attachments/Pasted%20image%2020220718183942.png)

## Base case

--> If we reach at `NULL` node then we will return `ans` and also we have to initialise it with `-1` because if the ans is not possible then it will contain `-1` and we will return `-1`.

## Final Code:

```cpp
// initialising with -1 because if the ceil is not possible then we will return -1
int ans = -1;
int findCeil(Node* root, int input) {
    if (root == NULL) return ans;
    // if current node is greater than input then goto left
    if(root->data >= input){
	    // update ans every time because we want closest max value
        ans = root->data;
        findCeil(root->left,input);
    // else goto right
    }else{
        findCeil(root->right,input);
    }
    return ans;
}
```

