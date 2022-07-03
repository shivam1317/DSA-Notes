## problem:

>Given a string **s** and a dictionary of words **dict** of length **n****,** add spaces in **s** to construct a sentence where each word is a valid dictionary word. Each dictionary word can be used more than once. Return all such possible sentences.
Follow examples for better understanding.

## Example:

**Input:** 
```
s = "catsanddog", n = 5 
dict = {"cats", "cat", "and", "sand", "dog"}
```
**Output:** 
```
(cats and dog)(cat sand dog)
```
**Explanation:** 
```
All the words in the given sentences are present in the dictionary.
```

## Approach:

--> Here we have given some words which we have to form from `s` so we can use `recursion` to add each character in our temp string and check if it's valid dictionary word then we will add space in temp string and when we will reach base condition then we will return.

So first here we have to take a map in which we will mark the frequency of every word as `1` because it will be easy for us to check later for if that word is a part of dict or not.

Once we will find any word then we will make temp as `s.substr(i+1)` where i will be from the loop of `0 to s.size()` and after making temp we will add one more space to seperate them.

Code will look like this:

```cpp
for(int i=0;i<s.size();i++){
			// making word till i+1
            string temp2 = s.substr(0,i+1);
			// If it's part of dictionary then add space after that word and combine it with temp
            if(mp[temp2] == 1){
                temp2 += ' ';
				// call for remaining string because we have already considered it
                solve(s.substr(i+1),ans,n,temp+temp2);
            }
        }
```

## base case:

--> now if our string will become empty or `s.size() == 0` then we will add the `temp` answer in our vector of strings and return.

```cpp
if(s.size() == 0){
            temp.pop_back();
            ans.push_back(temp);
            return;
        }
```

## Final code:

```cpp
unordered_map<string,int>mp;
    
    void solve(string s,vector<string>&ans,int n,string temp){
        if(s.size() == 0){
            temp.pop_back();
            ans.push_back(temp);
            return;
        }
        for(int i=0;i<s.size();i++){
            string temp2 = s.substr(0,i+1);
            if(mp[temp2] == 1){
                temp2 += ' ';
                solve(s.substr(i+1),ans,n,temp+temp2);
            }
        }
    }
    vector<string> wordBreak(int n, vector<string>& dict, string s)
    {
        for(auto it:dict){
            mp[it]++;
        }
        vector<string>ans;
        solve(s,ans,n,"");
        return ans;
    }
```

