## Problem:

>Given a sorted array and a number `key`, find the index of the first and last occurrence of the key in the array.
If the key is not present, return `[-1, -1]`.

## Example:

```
Array: [1, 2, 3, 3, 3, 4, 4, 5]
Number: 3
Answer: [2, 4]
```

## Approach:

--> Here we will need to do 2 binary searches. one for finding left range and one for right range. the only difference between these 2 binary searches will be: 

```
1. for left range if we find any element same as key then we will goto left side and store current index as one answer.
2. for right range if we find any element same as key then we will goto right side and store current index as one answer.
```

## Final Code:

```cpp
vector<int> searchRange(vector<int> &arr, int key) {
	vector<int>ans(2);
	// For left range
    int low = 0,high = arr.size()-1;
	int res = -1;
	while(low<=high){
		int mid = low + (high-low)/2;
		if(arr[mid] == key){
			res = mid;
			high = mid - 1;
		}
		else if(key < arr[mid]){
			high = mid - 1;
		}else{
			low = mid+1;
		}
	}
	ans[0] = res;
	low = 0;
	high = arr.size()-1;
	res = -1;
	// For right range
	while(low <= high){
		int mid = low + (high-low)/2;
		if(key == arr[mid]){
			res = mid;
			low = mid+1;
		}
		else if(key >= arr[mid]){
			low = mid+1;
		}else{
			high = mid-1;
		}
	}
	ans[1] = res;
	return ans;
}
```

