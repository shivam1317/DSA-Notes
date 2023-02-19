>[!summary] Problem statement
>Two of the nodes of a Binary Search Tree (BST) are swapped. Fix (or correct) the BST by swapping them back. Do not change the structure of the tree.
**Note:** It is guaranteed than the given input will form BST, except for 2 nodes that will be wrong.

## Example

**Input**:
```
	   10
     /    \
    5      8
   / \
  2   20
```
**Output:** 
```
1
```
**Explanation:**

![](../GFG/Attachments/Pasted%20image%2020230219154356.png)

## Approach:

--> so we know that `inorder of BST will give us sorted array` but here 2 nodes are swapped so we just have to findout the 2 elements which are breaking sorted array and then we just have to swap these 2 elements.

--> So first we will find the inorder array of the given tree and then we will maintain `3` variables:

```
1. prev -> which will tell us the previous element of current node in inorder list
2. first -> it will be the first element needs to be swapped (we will assign the first element to element which we will break the sorted array first time)
3. second -> it will be the second element needs to be swapped.
```

> All these elements will be `NULL` initially and passed `by reference`.

Now let's dry run this logic for one example for better understanding.

Suppose we have this tree.

![](../GFG/Attachments/Pasted%20image%2020230219155809.png)

we can see that `20` and `8` are the elements which needs to be swapped to make array sorted.

so we will start from `root` and we will check `if prev have any value and if its greater than current node's value` then that means we found one element. so we will check `if first is NULL then we will assign prev to it` and we will assign `root to second`.

Code:

```cpp
// goto left
if(prev && root->data < prev->data){
	if(first == NULL){
		first = prev;
	}
	second = root;
}
prev = root;
// goto right
```

### Now why we are assigning prev to first and root to second?

--> Look at the dry run of the above example:

| | |
|--|--|
|Iteration 1| Iteration 2|
|![](../GFG/Attachments/Pasted%20image%2020230219161528.png)|![](../GFG/Attachments/Pasted%20image%2020230219161556.png)|
|Iteration 3| Iteration 4|
|![](../GFG/Attachments/Pasted%20image%2020230219161916.png)|![](../GFG/Attachments/Pasted%20image%2020230219162029.png)|

## Final code:

```cpp
void solve(Node* &root,Node* &prev,Node* &first,Node *&second){
	// base case
	if(root ==NULL){
		return;
	}
	solve(root->left,prev,first,second);
	if(prev && root->data < prev->data){
		if(first == NULL){
			first = prev;
		}
		second = root;
	}
	prev = root;
	solve(root->right,prev,first,second);
}
struct Node *correctBST(struct Node *root) {
	 Node *first = NULL;
	 Node *second = NULL;
	 Node *prev = NULL;
	solve(root,prev,first,second);
	// swap the first and second
	swap(first->data,second->data);
	return root;
}
```

#tree #BST 