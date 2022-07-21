## Problem:

>Now, we'll try to solve a famous stack problem.
You are given an array **A** of size **N**. You need to first push the elements of the array into a stack and then print minimum in the stack at each pop.

[Problem Link](https://practice.geeksforgeeks.org/problems/get-min-at-pop/1)

## Example:

**Input**:
```
N = 5
A = {1 2 3 4 5}
```
**Output**: 
```
1 1 1 1 1
```
**Explanation**: 
```
After pushing elements to the stack, 
the stack will be "top -> 5, 4, 3, 2, 1". 
Now, start popping elements from the stack
popping 5: min in the stack is 1.popped 5
popping 4: min in the stack is 1. popped 4
popping 3: min in the stack is 1. popped 3
popping 2: min in the stack is 1. popped 2
popping 1: min in the stack is 1. popped 1
```

## Approach:

--> So in this question we have 2 functions and in first function we have to add all array elements in stack and in second function we have to print the lowest element in stack while popping element from stack.

--> So we can find the lowest element in stack during insertion only. we will maintain one `mini` variable which will store the minimum element till now and each time during inserting a element in stack we will check if the element which we are gonna insert is less than mini or not.

```
If the element is greater than mini then we will insert mini in stack.
If the element is smaller than mini then we will make element as mini and insert in stack.
```

## Final Code:

```cpp
stack<int> _push(int arr[],int n)
{
// first element is minimum for now
   int mini = arr[0];
   stack<int>s;
   // insert first element in stack
   s.push(mini);
   for(int i=1;i<n;i++){
   // If element is lower than mini then change mini
       if(arr[i] < mini){
           mini = arr[i];
       }
       // add mini in stack
       s.push(mini);
   }
   return s;
}

//Function to print minimum value in stack each time while popping.
void _getMinAtPop(stack<int>s)
{
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
}
```

