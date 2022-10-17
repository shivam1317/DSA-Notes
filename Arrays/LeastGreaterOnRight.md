>[!Problem Statement]
>Given an array **arr[]** of **N** integers and replace every element with the least greater element on its right side in the array. If there are no greater elements on the right side, replace it with **-1.**

## Example

**Input:**
```
arr[] = {8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28}
```
**Output:** 
```
{18, 63, 80, 25, 32, 43, 80, 93, 80, 25, 93, -1, 28, -1, -1}
```
**Explanation:** 
```
The least next greater element of 8 is 18.
The least next greater element of 58 is 63 and so on.
```

## Approach:

--> I first tried to think in brute force way by storing `index and element` in set and it will be sorted automatically and after that in another loop i will find the next element's next element in set and then check the indexes of both but it didn't worked :(

--> Now there is one observation that for the last element, the answer will be always `-1` so why don't we start from end of the array and go till 0th index. also set have one inbuilt method called `upper_bound` which will give the iterator of given element's next greater element so we will use that.

## Code:

```cpp
vector<int> findLeastGreater(vector<int>& arr, int n) {
        set<int>s;
        vector<int>ans(n,-1);
        for(int i=n-1;i>=0;i--){
            auto it = s.upper_bound(arr[i]);
            // If that element exists then we will add it in our answer vector
            if(it!=s.end()){
                ans[i] = *it;
            }
            s.insert(arr[i]);
        }
        return ans;
}
```

#upper_bound #set