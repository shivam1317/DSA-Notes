>[!Problem Statement]
>Given an array **A[ ]** of **N** of  integers, find the index of values that satisfy **A + B = C + D** where **A,B,C** & **D** are integers values in the array.  
>**Note:** As there may be multiple pairs satisfying the equation return lexicographically smallest order of  A, B, C and D and return all as -1 if there are no pairs satisfying the equation.

## Example:

**Input:**
```
N = 7
A[] = {3, 4, 7, 1, 2, 9, 8}
```
**Output:**
```
0 2 3 5
```
**Explanation:**
```
A[0] + A[2] = 3+7 = 10
A[3] + A[5] = 1+9 = 10
```

## Approach:

--> One approach for this problem will be to try all possible combinations and check which pairs are giving same sum and by this process find the lexicographically smalles pair index.

We will use similar logic here but we will use `unordered_map` to store the sum value and it's indexes so that if we again find same sum then we can take indexes of it's previous element and take index of current sum and store it in ans and keep doing this to find minimum ans.

>[!tip]
>You can find minimum of vectors as you do with variables
>```cpp
>vector<int>a = {1,2,3,4}
>vector<int>b = {3,5,4,2};
>vector<int>c = min(a,b);
>```

So using this functionality of vectors we will find the lexicographically smallest answer.

## Final Code:

```cpp
vector<int> satisfyEqn(int A[], int N) {
	unordered_map<int,pair<int,int>>mp;
	// Initialising ans with INT_MAX because we want minimum ans.
	vector<int>ans(4,INT_MAX);
	for(int i=0;i<N-1;i++){
		for(int j=i+1;j<N;j++){
			int sum = A[i] + A[j];
			// Finding if sum is already present or not in map
			if(mp.find(sum) != mp.end()){
				// we want unique indexes in pair that's why we are checking this 
				if(mp[sum].first != i && mp[sum].second != i && mp[sum].first != j && mp[sum].second != j){
					vector<int>v = {mp[sum].first,mp[sum].second,i,j};
					ans = min(ans,v);
				}
			}else{
				mp[sum] = make_pair(i,j);
			}   
		}
	}
	// If ans is not present then we will just return array of -1
	if(ans[0] == INT_MAX){
		return {-1,-1,-1,-1};
	}
	return ans;
}
```