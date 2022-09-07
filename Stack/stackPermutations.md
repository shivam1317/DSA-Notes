## Problem:

>You are given two arrays **A** and **B** of unique elements of size **N**. Check if one array is a stack permutation of the other array or not.  
Stack permutation means that one array can be created from another array using a stack and stack operations.

## Example:

**Input:**
```
N = 3
A = {1,2,3}
B = {2,1,3}
```

**Output:**
```
1
```

**Explanation:**
```
1. push 1 from A to stack
2. push 2 from A to stack
3. pop 2 from stack to B
4. pop 1 from stack to B
5. push 3 from A to stack
6. pop 3 from stack to B
```

## Approach:

--> Here we know that we have to make `B` array from `A` using stack so we will do as the problem says. 

First we will make 2 pointers `i and j`. i will traverse A and j will traverse B.now we will add one array in stack and we will traverse the second array in loop so if we get `st.top() and arr[i]` same then we will pop it from stack and if they are not same then we will add element from array to stack.

### Now the question is which array will be added to stack and which array we will use to compare?

--> So here we know that we have to make `B` array from `A` so we will add elements of `A` array in stack and compare them with elements of `B`.

So we will compare them in this way:

```
1. If st.top() is same as B[j] then we will pop all elements from stack which are same.
2. If they are not same then we will simply add A[i] in stack and increase i.
```

## Final Code:

```cpp
int isStackPermutation(int N,vector<int> &A,vector<int> &B){
	stack<int>st;
	int i=0,j=0;
	while(i < N && j < N){
		// If both are same
		if(A[i] != B[j]){
			st.push(A[i]);
			i++;
		// If they are not same
		}else{
			st.push(A[i]);
			i++;
			while(!st.empty() && st.top() == B[j]){
				st.pop();
				j++;
			}
		}
	}
	if(st.empty()){
		return true;
	}
	return false;
}
```


