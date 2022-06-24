## problem:

>Given a string '**s**'. The task is to find the **smallest** window length that contains all the characters of the given string at least one time.  
For eg. A = **aabcbcdbca**, then the result would be 4 as of the smallest window will be **dbca**.

## Example:

Input : 
```
"GEEKSGEEKSFOR"
```
Output : 
```
8
```
Explanation : 
```
Sub-string -> "GEEKSFOR"
```

## Approach:

--> Here first we have to find the substring which contains all the characters of the original string. so we will use `2` maps here: mp1 for storing the frequency of elements in original string. mp2 for finding the window with all string characters.

--> here we will take 2 pointers: i and j. `i` will increase by 1 till mp2.size() becomes equal to mp1.size() means if they both have same size that means `mp2` have all the characters of string and now we got one window. 

--> so once we get window, we will try to make it as smaller as possible by increasing `j`
and keep storing the answer in `ans` variable. Also we have to ensure that `j` stays less than `i`. Also in this while loop, if we increase `j` then we will decrease the frequency of `str[j]` by 1 and if it's frequency becomes `0` then we will `erase it from map` so that we can get out of while loop.

## Code:

```cpp
int findSubString(string str)
    {
        unordered_map<char,int>mp1;
        int n = str.length(),count = 0;
        for(int i=0;i<n;i++){
            mp1[str[i]]++;
        }
        unordered_map<char,int>mp2;
        int i = 0,j=0;
        int ans = INT_MAX;
        while(i<str.size()){
            mp2[str[i]]++;
            i++;
            if(mp2.size() == mp1.size()){
                ans = min(ans,i-j+1);
                while(mp2.size() == mp1.size() && j<i){
                    mp2[str[j]]--;
                    if(mp2[str[j]] == 0){
                        mp2.erase(str[j]);
                    }
                    j++;
                    ans = min(ans,i-j+1);
                }
            }
        }
        return ans;
    }
```

