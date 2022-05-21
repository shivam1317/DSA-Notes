## Problem:

> You have been given an N\*M matrix filled with integer numbers, find the maximum sum that can be obtained from a path starting from any cell in the first row to any cell in the last row.
> From a cell in a row, you can move to another cell directly below that row, or diagonally below left or right. So from a particular cell (row, col), we can move in three directions i.e.

```
Down: (row+1,col)
Down left diagonal: (row+1,col-1)
Down right diagonal: (row+1, col+1)
```

## Example:

### Input 1 :

```
2
4 4
1 2 10 4
100 3 2 1
1 1 20 2
1 2 2 1
3 3
10 2 3
3 7 2
8 1 5
```

### Output 1 :

```
105
25
```

### Explanation Of Input 1 :

```
In the first test case for the given matrix,
```

![Example](https://files.codingninjas.in/maxpath-5169.jpg)

```
The maximum path sum will be 2->100->1->2, So the sum is 105(2+100+1+2).

In the second test case for the given matrix, the maximum path sum will be 10->7->8, So the sum is 25(10+7+8).
```

## Approach:

--> Here both starting and ending points are not fixed so we have to calculate all the possibilities for starting and ending point like this:

![](./Attachments/Pastedimage20220521180535.png)

So we will find max path sum for all elements in the row and then count the maximum of them.

```cpp
for(int i=0;i<n;i++){

}
```
