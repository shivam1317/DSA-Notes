>[!Problem Statement]
> Given a row wise sorted matrix of size **R*C** where R and C are always **odd**, find the median of the matrix.

## Example:

**Input**:
```
R = 3, C = 3
M = [[1, 3, 5], 
     [2, 6, 9], 
     [3, 6, 9]]
```
**Output:** 
```
5
```
**Explanation**: 
```
Sorting matrix elements gives 
us {1,2,3,3,5,6,6,9,9}. Hence, 5 is median.
```

## Approach:

--> Here the matrix is sorted row-wise so first algo comes into my mind is `binary search` because to use binary search, the data structure must be sorted.

### Now How we will use binary search here?
--> we will consider every number in range of `max possible ans and min possible ans` and take mid everytime and then we will find the number of elements which are `smaller than current considered temp ans` and if the `number of elements is less than or equal to n/2` then we will move our low pointer ahead because to reach a precise value of median we have to go right side and if it's not the case then we will decrease high pointer.

>[!tip]
>Median have equal number of elements less than or greater than it

### What will be the max possible and min possible ans?

--> From the constrains given in question, the min possible ans will be 0 and max ans will be 2000.

### How we will count the number of elements less than current median?

--> For that we will run a loop for every row from `0 to r` and for each row we will run another binary search to find number of elements less than current median.

In this binary search, we will put low pointer at 0 and high pointer at `c-1`(last element in current row) and then we will do following:

```
1. If matrix[current_row][mid] is less than current_median, then we will increase low pointer. 
2. If matrix[current_row][mid] is greater than current_median, then we will decrease high pointer. 
```

--> After this inner binary search, we will add the value of low pointer in our `count` variable.
we are adding low pointer's value here because it will contain the count of elements less than current_median.

>[!note]
>Count variable will store the count of elements less than or equal to current_median

## Final Code:

```cpp
int median(vector<vector<int>> &matrix, int r, int c){
	int low = 0,high = 2000;
	while(low <= high){
		int temp_median = low + (high-low)/2;
		int count = 0;
		for(int i=0;i<r;i++){
			int lo = 0,hi=c-1;
			while(lo<=hi){
				int mid = lo + (hi-lo)/2;
				if(matrix[i][mid] <= temp_median){
					lo = mid + 1;
				}else{
					hi = mid - 1;
				}
			}
			count += lo;
		}
		// n will contain total number of elements 
		int n = r*c;
		if(count <= n/2){
			low = temp_median + 1;
		}else{
			high = temp_median - 1;
		}
	}
	return low;
}
```

#binarysearch #matrix 