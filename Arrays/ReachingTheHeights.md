## Problem:

>The teacher gives a mental ability question to Raju. The question is as follows:-
Raju is in an elevator. Given by his teacher is an array of size N which denotes the number of floors and has a 1 based indexing. The elevator starts from the ground and moves up and down, X and Y floors respectively. There is a code used in the elevator according to which it moves up X floors given at odd indexes of the array and moves down Y floors given at even indexes of the array. He is asked to go to the highest floor possible. Help him to sort the array such that he reaches the highest floor after traversing the whole array from starting till the end, without skipping any index.
He always prefers to move more number of floors up and less number of floors down. Once he gets into the elevator, the elevator should not reach the ground again, if it does return -1.

## Example:

**Input :** 
```
arr[] = {2, 3, 4, 5}
```
**Output :** 
```
5 2 4 3
```
**Explanation:**
```
Array can be arranged as {5,3,4,2} or {4,3,5,2} or {4,2,5,3} but it will get arranged as {5,2,4,3} because he always prefer to move more number of floors up and less number of floors down.
```

## Approach:

--> So here we know that we have to place the `greater number at odd index and small number at even index` so first we can sort the array and then maintain 2 pointers `low & high`.

low will be `0` and high will be `n-1` at start.
also we will make another vector which will be our answer.

After sorting the array, we will add the element at `arr[high]` in our ans vector and then we will add element at `arr[low]` and increase `low` and decrease `high`. we will do this procedure till low becomes greater than high.

Also we have to make sure that elevator don't come to ground again so for that we will maintain one `tempSum` variable in which we will add element if we are adding `arr[high]` in our ans and we will subtract the element if we are adding `arr[low]` in ans because we know that `the elements at odd position will go up and the elements at even position will go down`.

--> At any point `tempSum` becomes 0 then we will return `{-1}`

## Edge case:

==> If `low becomes same as high` then we will only add `arr[high]` or `arr[low]` but we will add current element in `tempSum` because we know that if `low is same as high` then we must be at odd position so that we will go up.

```cpp
if(low == high){
	tempSum += arr[high];
	ans.push_back(arr[high]);
	high--;
}
```

## Final code:

```cpp
vector<int> reaching_height(int n, int a[]) {
    vector<int>arr;
	// sorting the array
    sort(a,a+n);
    int low = 0,high = n-1;
    int tempSum = 0;
    while(low<=high){
		// edge case
        if(low == high){
            arr.push_back(a[high]);
            tempSum += a[high];
            high--;
        }else{
            arr.push_back(a[high]);
            tempSum += a[high];
            arr.push_back(a[low]);
            tempSum -= a[low];
            high--;
            low++;
        }
        
        if(tempSum == 0){
            return {-1};
        }
    }
    return arr;
```