## Problem:

```
Consider a special family of **Engineers** and **Doctors** with following rules :
1.  Everybody has two children.
2.  First child of an Engineer is an Engineer and second child is a Doctor.
3.  First child of an Doctor is Doctor and second child is an Engineer.
4.  All generations of Doctors and Engineers start with Engineer.
```

We can represent the situation using below diagram:

![](../GFG/Attachments/Pasted%20image%2020220624153857.png)

## Example:

**Input:**

```
level = 4, pos = 2
```

**Output:**

```
Doctor
```

**Explaination:**

```
It is shown in the tree given in question.
```

## Approach:

--> From the diagram we can see 2 conditions:

1. If current node's position is even then they will be have opposite profession as parent.
2. If current node's position is odd then they will have same position as parent.

--> So we can run recursive loop and check the parent of current node and also we will check the position and return the value according to the above 2 conditions.

### Base case:

If we reach at level `1` then we will return `e` because we know that the root node is always `e`

## Code:

```cpp
char profession(int level, int pos){
		// Base condition
        if(level == 1 || pos == 1){
            return 'e';
        }
	// If parent is doctor
        if(profession(level-1,(pos+1)/2) == 'd'){
            if(pos%2 == 0){
                return 'e';
            }
            return 'd';
        }
	// If parent is engineer
        else{
            if(pos%2 == 0){
                return 'd';
            }
            return 'e';
        }
    }
```
