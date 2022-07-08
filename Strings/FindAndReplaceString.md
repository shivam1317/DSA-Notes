## Problem:

>Given a string **S** on which you need to perform **Q** replace operations.  
Each replacement operation has 3 parameters: a starting index i, a source word x and a target word y. The rule is that if x starts at position i in the **original** **string S**, then we will replace that occurrence of x with y. If not, we do nothing.  
**Note:** All these operations occur simultaneously. It's guaranteed that there won't be any overlap in replacement: for example, S = "abc", indexes = [0,1], sources = ["ab", "bc"] is not a valid test case.

## Example:

**Input**: 
```
S = "gforks"
Q = 2
index[] = {0, 4}
sources[] = {"g", "ks"}
targets[] = {"geeks", "geeks"}
```

**Output**:
```
geeksforgeeks
```
**Explanation**:
```
"g" starts at index 0, so, it's reaplaced by "geeks". Similarly, "ks" starts at index 4,
and is replaced by "geeks".
```

## Approach:

--> Here we will simply traverse the whole string and then we will check `If the i is present in index array or not` and if it's present then we will check the string at ith index with the string in `sources` array and if they both are same then we will add the string in `targets` for that source in our ans string.

we will maintain one `count` variable which will traverse the `index`,`sources` and `targets` arrays. 

Whole process will look like this:

![](../DP/Attachments/Pasted%20image%2020220522143200.png)

## Code:

```cpp
string findAndReplace(string S ,int Q, int index[], string sources[], string targets[]) {
        string ans = "";
        int count = 0;
        for(int i=0;i<S.size();i++){
			// Count must not exceed Q so that's why we have written second condition
            if(index[count] == i && count < Q){
				// Here we have to check whole string given in sources array so that's why we are taking substring instead of single character 
                if(S.substr(i,sources[count].size()) == sources[count]){
                    ans += targets[count];
					// Now we will increase i to skip the characters which are already counted in substring so that we don't take them again
                    i+= sources[count].size()-1;
                }
				// If strings are not same then we will simply add S[i] in ans
                else{
                    ans += S[i]; 
                }
                count++;
            }
			// If i is not present in index array then we will add S[i] in ans
            else{
                ans += S[i];
            }
        }
        return ans;
    }
```
