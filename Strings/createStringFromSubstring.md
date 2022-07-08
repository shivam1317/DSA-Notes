## Problem:

>Given a string s, the task is to check if it can be constructed by taking a substring of it and appending multiple copies of the substring together

## Example 1:

**Input:** 
```
s = "ababab"
```
**Output:** 
```
1
```
**Explanation:** 
```
It is contructed by appending "ab" 3 times
```

## Example 2:

**Input:** 
```
s = "ababac"
```
**Output:** 
```
0
```
**Explanation:** 
```
Not possible to construct
```

## Approach:

--> So here first we have to find the longest repeating substring in the string `s`. we can find that using `queue` by checking 2 conditions:

```
1. If q.front() is same as s[i] then pop one element from queue and add s[i] in queue
2. If q.front() is not same as s[i] then just add s[i] in queue.
```

It will look like this:

```cpp
for(int i=1;i<s.size();i++){
	if(q.front() == s[i]){
		q.pop();
	}
	q.push(s[i]);
}
```


After doing that we will check if `q.size() is equal to s.size()` because if it's true then the string have distinct characters so we can't create that string using it's substring so we will return `false`.

```cpp
if(q.size() == s.size()){
	return false;
}
```

--> Now if it's not the condition then we will again run the loop to check that the substring we found is correctly repeating in the `s` or not by running one more for loop from `0 to s.size()-1` and doing the same procedure as previous for loop but this time we will have some characters in queue and if it's longest repeating substring then `q.front() will be same as s[i]`

```cpp
for(int i=0;i<s.size();i++){
	if(q.front() != s[i]){
		return false;
	}
	q.pop();
	q.push(s[i]);
}
return true;
```

## Code:

```cpp
int isRepeat(string s)
	{
	    queue<int>q;
	    q.push(s[0]);
	    // Finding repeating substring
	    for(int i=1;i<s.size();i++){
	        if(q.front() == s[i]){
	            q.pop();
	        }
	        q.push(s[i]);
	    }
	    if(q.size() == s.size()){
	        return false;
	    }
	    // Checking if we got currect common substring
	    for(int i=0;i<s.size();i++){
	        if(q.front() != s[i]){
	            return false;
	        }
	        q.pop();
	        q.push(s[i]);
	    }
	    return true;
	}
```