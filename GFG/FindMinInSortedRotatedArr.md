## Problem:

>Given an array of distinct elements which was initially sorted. This array is rotated at some unknown point. The task is to find the minimum element in the given sorted and rotated array.

## Example:

**Input:**
```
N = 10
arr[] = {2,3,4,5,6,7,8,9,10,1}
```

**Output:** 
```
1
```
**Explanation:** 
```
The array is rotated once anti-clockwise. So minium element is at last index (n-1) 
which is 1.
```

## Approach:

--> I found one pattern that if the array is rotated then at some point one element will be ==lesser than both arr[i-1] and arr[i+1]== and that point will be our minimum element.

So i started my loop from `1 to n-2` and checked this condition :

```cpp
int smaller = INT_MAX;
if(arr[i] < arr[i-1] && arr[i] < arr[i+1]){
	// If true then store the arr[i] in one variable and break this loop
	smaller = arr[i];
	break;
}
// At last find the min of arr[0],arr[n] and smaller.
```

but it will take `O(N)` complexity in worst case so here we will use ==binary search==

--> In binary search we will find `mid` first and check ==If mid is greater than the arr[low] then the previous part of mid is already sorted== so we will make mid as starting point.

--> ==if mid is lower than the arr[low] then we will goto left side of mid== because the array must be rotated somewhere in that part.

## Code:

```cpp
int minNumber(int arr[], int low, int high)
    {
        int s = low;
        int e = high;
        int mid = (s+e)/2;
        while(s<e){
            if(arr[mid] >= arr[low]){
                s = mid+1;
            }else{
                e = mid;
            }
            mid = (s+e)/2;
        }
		// we can take anything arr[s] or arr[e] because they are gonna be same at last.
        if(arr[s]<arr[low]){
            return arr[s];
        }else{
            return arr[low];
        }
    }
```



