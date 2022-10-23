>[!Problem Statement]
>A number is called a stepping number if all adjacent digits have an absolute difference of 1, e.g. '321' is a Stepping Number while 421 is not. Given two integers **n** and **m**, find the count of all the stepping numbers in the range [n, m].

## Example:

**Input:** 
```
n = 0, m = 21
```
**Output:** 
```
13
```
**Explanation:** 
```
Stepping no's are 0 1 2 3 4 5
6 7 8 9 10 12 21
```

## Approach:

--> Brute force solution for this problem will be run a for loop from `n to m` and for each number, convert it into string or without converting also just take it's one digit at a time and then check if the digits have difference of 1 or not. Sadly this logic will give `TLE`.

--> Now we know that the max stepping number will be `<=m` and also we know that we are just concerned about digits here. so we will run a loop from `1 to 9` and for each digit we will try to append some digits such that the absolute difference will be 1.

--> So for example, if we have digit `2` then we can only append `3` or `1` to it to make difference 1. and this logic will be valid for every numbers from `1 to 8` except `0 and 9` because we can't append `(0-1)` to any number and also we can't append `(9+1)` to any digit so we will also handle these edge cases.

So basically, we will keep appending such digits to current number and once that number becomes greater than `m`, we will return. also we will maintain one `count` variable to store our final ans.

## Base case:

--> we are running loop from `1 to 9` and not from `0 to 9` because for `0`, there is only one possibility which is `0` itself. because we can't append any number to `0` like `01,02,03... etc` so we will just add 1 to count if `n is 0`.

## Final code:

### DFS Solution:

```cpp
void dfs(int &count,int curr,int n,int m){
	// base case
	if(curr > m){
		return;
	}
	if(curr >= n && curr <=m){
		count++;
	}
	int rem = curr%10;
	if(rem >= 1 && rem <= 8){
		dfs(count,curr*10 + rem+1,n,m);
		dfs(count,curr*10 + rem-1,n,m);
	}
	// edge cases for 0 and 9
	else if(rem == 9){
		dfs(count,curr*10 + rem-1,n,m);
	}
	else{
		dfs(count,curr*10 + rem+1,n,m);
	}
	
}
int steppingNumbers(int n, int m)
{
	int count = 0;
	if(n == 0){
		count++;
	}
	for(int i=1;i<=9;i++){
		dfs(count,i,n,m);
	}
	return count;
}
```

### BFS Solution:

```cpp
int steppingNumbers(int n, int m)
{
	int count = 0;
	if(n == 0){
		count++;
	}
	queue<int>q;
	for(int i=1;i<=9;i++){
		q.push(i);
	}
	while(!q.empty()){
		int currNum = q.front();
		q.pop();
		if(currNum >= n && currNum <= m){
			count++;
		}
		if(currNum <= m){
			int rem = currNum%10;
			if(rem >= 1 && rem <= 8){
				q.push(currNum*10 + rem + 1);
				q.push(currNum*10 + rem - 1);
			}
			else if(rem == 9){
				q.push(currNum*10 + rem - 1);
			}
			else{
				q.push(currNum*10 + rem + 1);
			}
		}
	}
	return count;
}
```

#dfs #bfs 