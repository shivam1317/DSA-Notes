## Problem:

>**Geek** is organizing a party at his house. For the party, he needs exactly **N** donuts for the guests. **Geek** decides to order the donuts from a nearby restaurant, which has **L** chefs and each chef has a rank **R**.   
A chef with rank **R** can make 1 donut in the first **R** minutes, 1 more donut in the next **2R** minutes, 1 more donut in **3R** minutes, and so on.  
For example. a chef with rank 2, can make one donut in 2 minutes, one more donut in the next 4 minutes, and one more in the next 6 minutes. So, it take 2 + 4 + 6 = 12 minutes to make 3 donuts. A chef can move on to making the next donut only after completing the previous one. All the chefs can work simultaneously.  
Since, it's time for the party, **Geek** wants to know the **minimum** time required in completing **N** donuts. Return an integer denoting the minimum time

## Example:

**Input:**
```
N = 10
L = 4
rank[] = {1, 2, 3, 4}
```
**Output:** 
```
12
```
**Explanation:** 
```
Chef with rank 1, can make 4 donuts in time 1 + 2 + 3 + 4 = 10 mins
Chef with rank 2, can make 3 donuts in time 2 + 4 + 6 = 12 mins
Chef with rank 3, can make 2 donuts in time 3 + 6 = 9 mins
Chef with rank 4, can make 1 donuts in time = 4 minutes
Total donuts = 4 + 3 + 2 + 1 = 10 and total time = 12 minutes.
```

## Approach:

--> Whenever there is a problem saying find minimum of maximum or maximum then it can be solved with `binary search`.

So here also we have to `minimise the maximum taken time for each chef` so we will define 2 variables `low and high` and put low as `minimum element of array` and high as any high value like `1000007` and then we will check for every `mid` value if we can get total number of donuts made in `mid` time.

Now if it's greater than or equal to `N(which is required number of donuts)` then we have one valid answer but we need `minimum ans` so we will goto left side.

--> And if `mid` is not a valid answer then we will goto right side because if can't create `N` donuts in mid time then we also can't create it in lesser time than mid.

### Now how we will find total donuts made in mid time?

--> For that let's make one formula:

let's assume that one chef can make 1 donut in `R` time and we have to find total donuts in `mid` time so it will look like:

```
1R+2R+3R+...+NR = mid
```

Now after solving this equation it will look like this:

![](../GFG/Attachments/Pasted%20image%2020220903140531.png)

Now using this formula we can find total number of donuts 1 chef can make in `mid` time. so we have to do this for all chefs and find total donuts and if it's greater than or equal to `N` then we will goto left side or goto right side as discussed above.

## Final Code:

```cpp
bool isPossible(int mid,int N,vector<int>&A){
	int count = 0;
	for(int i=0;i<A.size();i++){
		// Our formula
		count += (-1 + sqrt(1+(8*mid)/A[i]))/2;
	}
	return count >= N;
}
int findMinTime(int N, vector<int>&A, int L){
	// this is function used to find minimum element in vector.
	int low = *min_element(A.begin(),A.end()),high = 1000007;
	int ans = high;
	while(low <= high){
		int mid = low + (high-low)/2;
		if(isPossible(mid,N,A)){
			ans = mid;
			high = mid-1;
		}else{
			low = mid+1;
		}
	}
	return ans;
} 
```

