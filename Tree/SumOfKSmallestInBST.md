## Problem:

>Given a Binary Search Tree. Find sum of all elements smaller than and equal to Kth smallest element.

## Example:

**Input:** 
```
          20
        /    \
       8     22
     /    \
    4     12
         /    \
        10    14   , K=3
```
**Output:** 
```
22
```
**Explanation:**
```
Sum of 3 smallest elements are: 
4 + 8 + 10 = 22
```

## Approach:

--> We know that the `inorder traversal` of BST will give us sorted array and here we need k smallest numbers so we will do inorder traversal here and we will also maintain one `sum` variable which will store the value of current node in sum.

--> After we add value in sum, we will decrease the value of `k` by 1 and we will keep doing this until `k` becomes 0.

>Also remember that we have to pass both sum and k by referance so that it will take original value.

>I tried to make sum variable as global but it was not giving right answer so i passed it in params.

## Base case:

if any node is root or k is 0 then we will return from it:

```cpp
if(root == NULL || k == 0){
	return;
}
```

## Final Code:

```cpp
void inorder(Node* root,int &k,int &ans){
    if(root == NULL || k == 0){
        return;
    }
    inorder(root->left,k,ans);
    if(k == 0){
        return;
    }
    ans += root->data;
    k--;
    inorder(root->right,k,ans);
}
int sum(Node* root, int k) 
{
    int ans = 0;
    inorder(root,k,ans);
    return ans;
} 
```

#tree #BST #inorder