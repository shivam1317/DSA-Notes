## Problem:

>Given the `head` of a linked list and a value `x`, partition it such that all nodes less than `x` come before nodes greater than or equal to `x`.
You should preserve the original relative order of the nodes in each of the two partitions.

```
Class Node:
    data (int)
    next (Node)
```

[Problem Link](https://leetcode.com/problems/partition-list/)

## Example:

**Input:** 
```
head = [1,4,3,2,5,2], x = 3
```
**Output:** 
```
[1,2,2,4,3,5]
```

Diagram:

![](../GFG/Attachments/Pasted%20image%2020220727163107.png)

## Approach:

Before going to actual implementation let's first discuss base case:

## Base case:

Base case 1: If head is NULL then we can't do anything so we will simply return head.
Base case 2: If `head->next` is NULL that means there is only one node so in this case also we will return head.

it will look like this in code:

```cpp
if(head == NULL || head->next == NULL){
	return head;
}
```

## Approach(Continue)

--> So first of all we will check if `head` is lower than `x` then we will add all future elements which will be less than `x` after `head` and if `head` is greater than or equal to `x` then we will `make one new node` and give it a value which is not in constrains (we will give 101) and all the future elements which will be lower than `x` will be added after this node(i.e. at start of linkedlist).

--> Let's look at diagram for this process:

Case 1:

![](../GFG/Attachments/Pasted%20image%2020220727165103.png)

Case 2:

![](../GFG/Attachments/Pasted%20image%2020220727171046.png)

--> Now we have found the initial nodes from where our answer linkedlist will start but now we have to `join the nodes which are lower than x after temphead`. So for that we will use 2 pointers `curr and prev`

we will make `prev = head and curr=head->next` we are doing this because we have already checked for head node in above 2 cases.

--> we will keep increasing prev and curr till `curr becomes less than x`. and if we find any curr becomes less than `x` now the actual process will begin.

So first of all we will make `prev->next` to `curr->next` because `curr` node is gonna move after `temphead`.

So let's see it step by step:
1. make `prev->next = curr->next`
2. Store the `temphead->next` in some temporary node because we will use it in future steps.
3. Now make `temphead->next = curr`
4. Now do `curr->next = the temporary node which we stored`
5. make `curr` new `temphead`.
6. and make `curr = curr->next` to goto next node.
7. Remember that `prev` will not change in this process.

This all process will look like this in code:

```
prev->next = curr->next;
ListNode* temp = temphead->next;
temphead->next = curr;
curr->next = temp;
temphead = curr;
curr = prev->next;
```

If `curr->data is not less than x` then we will simply go forward:

```
prev = curr
curr = curr->next
```

--> Now we have to return the new head and we can't return `temphead` because it's gonna modify everytime. so we will need `one more node called ans` which will initially point to `temphead` and at last we will return it.

This whole process will look like this:

```cpp
	if(head == NULL || head->next == NULL){
            return head;
	}
	ListNode* ans;
	ListNode* temphead = new ListNode();
	if(head->val >= x){
		temphead->val = 101;
		temphead->next = head;
		ans = temphead;
	}else{
		temphead = head;
		ans = temphead;
	}
	ListNode* prev = head;
	ListNode* curr = head->next;
	while(curr){
		if(curr->val < x){
			prev->next = curr->next;
			ListNode* temp = temphead->next;
			temphead->next = curr;
			curr->next = temp;
			temphead = curr;
			curr = prev->next;
		}else{
			prev = curr;
			curr = curr->next;
		}
	}
```

--> Now there are 2 other edge cases Let's check them out:

### Case 1: If all the elements in linkedlist are greater than x:

In this case our `temphead` will stay at dummy node and we will return `ans->next` because we know that ans is temphead and it's next pointer will be our new head.

>For example take 3->5->7->4->6 as linkedlist and x=2 and try by yourself.

```cpp
if(ans->val == 101){
	return ans->next;
}
```

### Case 2: If current is less than x and temphead->next is already current which means it's already at it's place.

In this case we will not do anything. we will just make `curr` as new temphead and make `prev` as curr and move curr forward i.e `curr = curr->next`.

>For example take 1->2->3->4->5 as linkedlist and x=5 and try by yourself. 

The above case will look like this:

```cpp
if(temphead->next == curr){
	temphead = curr;
	prev = curr;
	curr = curr->next;
	continue;
}
```

--> So now let's see the final code 😳:

## Final Code:

```cpp
ListNode* partition(ListNode* head, int x) {
	if(head == NULL || head->next == NULL){
		return head;
	}
	ListNode* ans;
	// dummy node
	ListNode* temphead = new ListNode();
	if(head->val >= x){
		temphead->val = 101;
		temphead->next = head;
		ans = temphead;
	}else{
		temphead = head;
		ans = temphead;
	}
	ListNode* prev = head;
	ListNode* curr = head->next;
	while(curr){
		if(curr->val < x){
			// If it's already at correct position
			if(temphead->next == curr){
				temphead = curr;
				prev = curr;
				curr = curr->next;
				continue;
			}
			// Else do the process which is described in approach section
			prev->next = curr->next;
			ListNode* temp = temphead->next;
			temphead->next = curr;
			curr->next = temp;
			temphead = curr;
			curr = prev->next;
		// if current node is not smaller than x then simply go forward
		}else{
			prev = curr;
			curr = curr->next;
		}
	}
	// if all elements are greater than x
	if(ans->val == 101){
		return ans->next;
	}
	// return ans
	return ans;
}
```

And we have solved the problem 😎:

![](../GFG/Attachments/Pasted%20image%2020220727181848.png)