## Problem:

>Geek lives in a special city where houses are arranged in a hierarchial manner. Starting from house number 1, each house leads to two more houses.    
1 leads to 2 and 3.   
2 leads to 4 and 5.   
3 leads to 6 and 7. and so on.   
Given the house numbers on two houses x and y, find the length of the shortest path between them.

## Example:

**Input:**
```
x = 2, y = 6
```
**Output:** 
```
3
```

Diagram:

![](Attachments/Pasted%20image%2020220528141933.png)

## Approach:

--> here we can see one pattern that `child is 2*parent or (2*parent)+1` so here we can keep dividing them by `2` and they will be same at one point which will be their `Lowest Common Ancestor(LCA)` 

And we will increase the `dist` variable in each iteration.

## Code:

```cpp
int shortestPath( int x, int y){ 
        int dist = 0;
        while( x != y){
            if(x>y){
                x = x/2;
            }else{
                y = y/2;
            }
            dist++;
        }
        return dist;
    }
```

