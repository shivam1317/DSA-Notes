>[!Problem Statement]
>Given an unsorted array, **Arr**[] of size **N** and that contains **even** number of occurrences for all numbers except two numbers. Find the two numbers in **decreasing** order which has **odd** occurrences.

## Example:

**Input:**
```
N = 8
Arr = {4, 2, 4, 5, 2, 3, 3, 1}
```
**Output:** 
```
{5, 1}
``` 
**Explaination:** 
```
5 and 1 have odd occurrences.
```

## Approach:

--> Now this question is very similar to `Find the single element` question in which we have an array with every element with even freq except one and we have to find that single element and we can do this easily with `XOR` because we know that `XOR of 2 same numbers will be 0`.

We can apply same logic here but here if we do xor of all numbers then the final xor we will get will be xor of 2 numbers which have odd frequencies and that's what we want.

### How we can get those numbers from this xor value?

--> For that let's take an example, suppose we have an array as `[4, 2, 4, 5, 2, 3, 3, 1]` then it's final xor will be `4(100 in binary)` which is xor of `5(101 in binary)` and `1(001 in binary)`.

So we know that if any bit is `1` in xor value, that means both numbers will have different bits i.e one number will have `1` at that place and other number will have `0` at that place because `1^0 = 1`.

So from the above logic, we will first have to find any one set bit place and then we will traverse the whole array again and we will divide numbers in 2 categories: 
```
1) numbers who have bit as set(1) at that place 
2) numbers who have bit as unset(0) at that place
```

### How to check this conditions?

--> we know that there are total `32` bits, so we will run a loop from `0 to 32` and for each place, we will do `number & (1<<i) (here i is ith value in 0->32 loop)`  and if it's `1` then it means the ith bit is set and if it's 0 then its unset.

Let's dry run this logic on above example,

we found that final xor for `[4, 2, 4, 5, 2, 3, 3, 1]` is `4(100)` and it have `3rd bit` set so we will check only `3rd` bit of each number and divide them according to set and unset.

![](../GFG/Attachments/Pasted%20image%2020221109005701.png)

In above image you can clearly see that we can do xor both sides and get our final answer!

![](../GFG/Attachments/Pasted%20image%2020221109005818.png)

## Final code:

```cpp
vector<long long int> twoOddNum(long long int Arr[], long long int N)  
{
	long long tempxor = 0;
	for(int i=0;i<N;i++){
		tempxor ^= Arr[i];
	}
	int setbit = 0;
	for(int i=0;i<32;i++){
		long long mask = 1<<i;
		if(mask&tempxor){
			setbit = mask;
			break;
		}
	}
	int set=0,notset=0;
	for(int i=0;i<N;i++){
		if(Arr[i]&setbit){
			set ^= Arr[i];
		}
		else{
			notset ^= Arr[i];
		}
	}
	return {max(set,notset),min(set,notset)};
}
```

#xor 