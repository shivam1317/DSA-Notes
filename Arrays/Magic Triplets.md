## Problem statement:

>Given an array of size n, a triplet (a[i], a[j], a[k]) is called a Magic Triplet if a[i] < a[j] < a[k] and i < j < k.  Count the number of magic triplets in a given array.
>[Problem link](https://practice.geeksforgeeks.org/problems/magic-triplets4003/1)

## Example:

**Input:** 
```
arr = [1, 2, 3, 4]
```
**Output:** 
```
4
```
**Explanation:** 
```
Fours magic triplets are 
(1, 2, 3), (1, 2, 4), (1, 3, 4) and (2, 3, 4).
```

## Approach:

--> Here we can take each number as `middle number` and then find smaller numbers than it on left side and bigger numbers than it on right side.

Once we get the smaller and greater numbers from both sides then we will add `smaller and greater` count and add it into our final ans.

### How exactly it's working?

--> Here we know that we have to find exact `3 numbers` which have `a[i]<a[j]<a[k] with i<j<k` so we are considering every element as `a[j]` here and then inding count of elements who can take place of `a[i]` on left side and similarly or `a[k]` and at last to consider all combinations, we are multiplying this count.

## Final code:

```cpp
int countTriplets(vector<int>nums){
	int ans = 0;
	for(int i=0;i<nums.size();i++){
		int small = 0;
		for(int j=0;j<i;j++){
			if(nums[j]<nums[i]){
				small++;
			}
		}
		int big = 0;
		for(int k=i+1;k<nums.size();k++){
			if(nums[k] > nums[i]){
				big++;
			}
		}
		ans += (small*big);
	}
	return ans;
}
```

#Array  