>[!Problem Statement]
>Construct a binary tree from a string consisting of parenthesis and integers. The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the roots value and a pair of parenthesis contains a child binary tree with the same structure. Always start to construct the left child node of the parent first if it exists.

## Example:

**Input:** 
```
"1(2)(3)"
``` 
**Output:** 
```
2 1 3
```
**Explanation:**
```
           1
          / \
         2   3
Explanation: first pair of parenthesis contains left subtree and second one contains the right 
subtree. Inorder of above tree is "2 1 3".
```

## Approach:

--> We can apply the logic of `parenthisis check` question where we used `stack` and this question is also similar to it. so we will use stack to store nodes and we will apply different logic on the basis of opening bracket (`(`) and closing bracket (`)`)

--> So first if it's `(` then we don't have to do anything so we will just continue.
--> If it's a integer then we will make node using that number and add it in our stack.

>[!tip]
>we can check if a character is an integer or not using `isdigit()` method.

Also we have to check one more condition where the number is of more than one digits, so for that we have to run a inner loop till character is a number.

```cpp
string temp = "";
while(isdigit(str[i])){
	temp += str[i];
	i++;
}
// Now convert this string into number
int num = stoi(temp);
```

--> If current character is `)` then we know that we have added some nodes in our stack and take 2 top nodes, which will be `child and parent` nodes. and then we will determine whether to make it left node or right node.

```
If parent don't have left node then we will make it left node
If parent have left node then we will make it right node
```

```cpp
// Newly added node will be child 
Node* child = st.top();
st.pop();
// we will node pop this node because we can use this to append childs and also this node will be appended to it's parent
Node* parent = st.top();
if(parent->left == NULL){
	parent->left = child;
}else{
	parent->right = child;
}
```

--> And we will follow this process till i is less than size of `str`.

## Final code:

```cpp
Node *treeFromString(string str){
	stack<Node*>st;
	for(int i=0;i<str.size();i++){
		if(str[i] == '('){
			continue;
		}
		else if(isdigit(str[i])){
			string temp = "";
			while(i<str.size() && isdigit(str[i])){
				temp += str[i];
				i++;
			}
			int num = stoi(temp);
			Node* node = new Node(num);
			st.push(node);
			// because for loop will increase the size of i so we have to subtract 1 from i
			i--;
		}
		// If str[i] is ')'
		else{
			Node* child = st.top();
			st.pop();
			Node* parent = st.top();
			if(parent->left == NULL){
				parent->left = child;
			}else {
				parent->right = child;
			}
		}
	}
	// At last there will be only one node left in our stack which will be root node of tree
	return st.top();
}
```

#binarytree #tree #stack 