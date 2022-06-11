## Problem :

>Given an array of **n** elements, where each element is at most **k** away from its target position, you need to sort the array optimally

## Example:

**Input:**
```
n = 7, k = 3
arr[] = {6,5,3,2,8,10,9}
```
**Output:** 
```
2 3 5 6 8 9 10
```
**Explanation:** 
```
The sorted array will be
2 3 5 6 8 9 10
```

## Approach:

--> First we will use min heap which we can make using priority queue and add first `K+1` elements in pq. after that we will traverse the array from `k+1` and then take the top of the priority queue which will be the smallest element in first `K` elements so we will add it in our `ans` vector and after that pop it and then we will add the another element in priority queue and keep doing it.

At last we will have `K` elements left in our min heap so we will also add them in our `ans` vector.

```cpp
 vector<int>nearlySorted(int arr[], int num, int K){
        priority_queue<int,vector<int>,greater<int>>pq;
        vector<int>ans;
        for(int i=0;i<=K;i++){
            pq.push(arr[i]);
        }
        for(int i=K+1;i<num;i++){
            ans.push_back(pq.top());
            pq.pop();
            pq.push(arr[i]);
        }
        while(!pq.empty()){
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
```