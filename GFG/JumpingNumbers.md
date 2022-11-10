>[!Problem Statement]
>Given a positive number **X**. Find the largest Jumping Number which is smaller than or equal to X.
>**Jumping Number:** A number is called Jumping Number if all adjacent digits in it differ by only 1. All single-digit numbers are considered as Jumping Numbers. For example **7**, **8987** and **4343456** are Jumping numbers but **796, 677** and **89098** are not.

## Example:

**Input:**
```
X = 10
```
**Output:**
```
10
```
**Explanation:**
```
10 is the largest Jumping Number
possible for X = 10.
```

## Approach:

--> The brute force solution for this problem will be to generate all numbers from `1 to X` and check if that number is jumping number or not but we have 69iq so we will try to optimise this.

--> instead of generating all numbers, we can just start with first `9` digits and then keep appending such digits which makes it jumping number and in each iteration, we will keep taking the max number. for this purpose we will use `queue`. 

### but do we really require to add all first 9 digits?

The answer is no.
--> Here we can observe that for each number, it's nearest jumping number will have starting digit `less than or equal to first digit of X` for example if we are finding jumping number for `73` then it's answer will be `67` whose first digit is `6` which is less than `7`.

so we will first find the first digit of number and add only digits which are less than or equal to first digit in queue.

After that we will take element from queue one by one and append specific digit to it which will make it jumping number. So for example if we have number `898` then we can only append `7` or `9` to it so we will try both ways and add both in queue.

## base case:

For `0` we can't append `lastDigit-1` and for `9` we can't append `lastDigit+1` so we have to keep that in mind.

## Final code:

```cpp
long long jumpingNums(long long X) {
	long long temp = X;
	// Finding first digit
	while(temp>10){
		temp/=10;
	}
	queue<long long>q;
	for(int i=1;i<=temp;i++){
		q.push(i);
	}
	long long ans = 0;
	while(!q.empty()){
		long long num = q.front();
		q.pop();
		// If number becomes greater than X then no need to check more just break the loop.
		if(num > X){
			break;
		}
		ans = max(ans,num);
		long long lastDigit = num%10;
		if(lastDigit != 0){
			long long num1 = num*10 + lastDigit - 1;
			q.push(num1);
		}
		if(lastDigit != 9){
			long long num2 = num*10 + lastDigit + 1;
			q.push(num2);
		}
	}
	return ans;
}
```