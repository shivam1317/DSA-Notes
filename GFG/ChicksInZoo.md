>[!Problem Statement]
>Initially, the zoo have a single chick. A chick gives birth to 2 chicks every day and the life expectancy of a chick is 6 days. Zoo officials want to buy food for chicks so they want to know the number of chicks on an Nth day. Help the officials with this task.

## Example:

**Input:** 
```
N = 2 
```
**Output:** 
```
3
```
**Explanation:** 
```
First day there is only 1 chick.
On second day total number of chicks = 3.
```

## Approach:

--> If we take a look at number of chicks for first 5 days then it will look like this:

![](Attachments/Pasted%20image%2020221030170335.png)

--> Here we can see that we are taking previous chicks and multiplying them by 2 and adding them in total chicks count.

So here we have to maintain one storage which will store the number of chicks borned on ith day and from that storage we can get total number of chicks. And also we have to check that if `i > 6` then we have to remove the dead chicks because one chick can survive only 6 days.

so we will use map here to store the number of chicks and also we will maintain 2 variables: total and dead which will store the total chicks and dead chicks count.

## Final code:

```cpp
long long int NoOfChicks(int n){
	unordered_map<int,long long int>mp;
	// it will store total chicks
	long long int ans = 1;
	// it will store dead chicks
	long long int dead = 1;
	mp[1] = 1;
	for(int i=2;i<=n;i++){
		if(i > 6){
			ans -= mp[dead];
			dead++;
		}
		// every chick can give birth to 2 chicks so we will add 2*ans in ith day's count
		mp[i] = 2*ans;
		ans += mp[i];
	}
	return ans;
}
```

#dp #misc 