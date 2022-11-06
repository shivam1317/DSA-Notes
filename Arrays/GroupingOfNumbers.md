>[!Problem Statement]
>One day Jim came across array **arr[]** of **N** numbers. He decided to divide these **N** numbers into different groups. Each group contains numbers in which sum of any two numbers should **not be divisible** by an integer **K**. Print the size of the group containing **maximum** numbers.

## Example:

**Input:**
```
N = 4, K = 8
arr[] = {1, 7, 2, 6}
```
**Output:**
```
2
```
**Explanation:**
```
The  group of numbers which can be formed
are: (1),(2),(7),(6),(1,2),(1,6),(7,2),(7,6).
So,the maximum possible size of the group is 2.
```

## Approach:

--> Here the brute force solution will be to generate all the subsequences and check if they are valid or not.

>[!note]
>Any subsequence will be only valid if we select any 2 elements from that subsequence then it's sum must not be divisible by k. 
>Also remember that we are only concerend about any 2 elements only. 

--> To optimise this logic, we will take remainders of every element after dividing it with k so that we only have to worry about numbers between `0 and k-1` because remainders can't be greater than or equal to K. also we will store frequency of these remainders in array or map.

Now there is one observation which is:
```
if sum of a and b is divisible by k then 
a%k + b%k == k
``` 

From above observation, we know that we can't take 2 remainders if their sum is equal to `K` but we can take any one number from it. For example if we talk about remainders `1 and 7 and K is 8` then we can't take 1 and 7 in one subsequence because it will be divisible by 8 that's why we can take either `1` or `7`.

### But how we will decide which remainder to take?

--> Let's take one example for this:

Suppose remainders are like `2,2,2,6,3` and `K is 8` so we know that 2+6 will be 8 so we have to take either `6 or 2` so if we take `6` then subsequence will be `6,3` and it's size is 2 and if we take `2` then subsequence will be `2 2 2 3` and it's size is 4 which is greater than previous.

so from this we can conclude that,
```
we will take the remainder with bigger frequency because we want maximum length.
```

--> So we will take 2 pointers i and j, `i` will be start from 1 and `j` will be at `K-1` and we will increase i and decrease j simultaneously.

>we are not starting from 0 because remainder 0 means that element is divisible by k so we will first check if there any element exists with remainder 0 then we will only add 1 in our final count.

The while loop will look like this:

```cpp
int cnt = freq[0] ? 1 : 0;
int i = 1,j = K-1;
while(i < j){
	cnt += max(freq[i],freq[j]);
	i++;
	j--;
}
```

--> Now if `i==j` then also we will take that element only once because suppose our `k is 8 then we can take 4 once only because  4+4 will make it 8 and max(f(4),f(4)) makes no sence`.

## Final Code:

```cpp
int maxGroupSize(int arr[], int N, int K) {
	vector<int>freq(K,0);
	for(int i=0;i<N;i++){
		freq[arr[i]%K]++;
	}
	int cnt = freq[0] ? 1 : 0;
	int i = 1,j = K-1;
	while(i < j){
		cnt += max(freq[i],freq[j]);
		i++;
		j--;
	}
	if(i == j && freq[i]){
		cnt++;
	}
	return cnt;
}
```

#Array #subsequence 