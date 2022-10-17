## Problem:

>Bob, a teacher of St. Joseph School given a task by his principal to merge the details of the students where each element **details[i]** is a list of strings, where the first element **details[i][0]** is a name of the student, and the rest of the elements are emails representing emails of the student.   Two details definitely belong to the same student if there is some common email to both detail.  After merging the details, return the details of the student in the following format: the first element of each detail is the name of the student, and the rest of the elements are emails in sorted order. The details themselves can be returned in any order.  Note: Two details have the same name, they may belong to different people as people could have the same name. A person can have any number of details initially, but all of their details definitely have the same name.  
**Note:** In case 2 or more same email belongs to 2 or more different names merge with first name only.

## Example:

**Input:** 
```
n: 4
details = 
[["John","johnsmith@mail.com","john_newyork@mail.com"],
["John","johnsmith@mail.com","john00@mail.com"],
["Mary","mary@mail.com"],
["John","johnnybravo@mail.com"]]
```
**Output:** 
```
[["John","john00@mail.com","john_newyork@mail.com",
"johnsmith@mail.com"],["Mary","mary@mail.com"],
["John","johnnybravo@mail.com"]]
```
**Explanation:**
```
The first and second John's are the same person as 
they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none
of their email addresses are used by other accounts.
We could return these lists in any order, for example
the answer [['Mary', 'mary@mail.com'], 
['John', 'johnnybravo@mail.com'], 
['John', 'john00@mail.com', 'john_newyork@mail.com', 
'johnsmith@mail.com']] 
would still be accepted.
```

## Approach:

--> So in this question we have to merge all the emails if 2 people have the same email (even if they have different names). and also these emails must be in `sorted order`.

So we will require one `vector of set` to store these mails so that they stay distinct and in sorted order. 

--> Now we also have to consider the name only once so we will make one separate array called `names.` in which we will only store names. 

--> We also have to maintain which mail is associated with which user so for that we will use one `unordered_map` and for each email we will give one `id` to that email to identify the owner of the email.

> We will start id from 1 because the default values for each key in map is 0.

So from above explaination we can conclude that we need 5 things:

```
1. vector of set to store emails
2. vector of string to store names
3. unordered_map to store ids for every email
4. id variable
5. Final vector<vector<string>> to store our answer
```

--> Now first we will iterate every array in `details` array one by one and check if any email is already considered or not and we can check by checking their ids.

```cpp
int id = 0;
// we are starting from 1st index because 0th index is name
for(int i=1;i<d.size();i++){
	id = max(id,mail_id[d[i]]);
}
```

And now if it's not has been visited then we will update id and initialise an empty set in `mail_id` vector and also push the name in `name` vector.

```cpp
// id is 0 means it's default value and it means it's not visited
if(id == 0){
	id = name.size();
	name.push_back(d[0]);
	mails.push_back(set<string>());
}
```

--> Now give specific ids to every mail in `mail_id` map and also add these mails in mails array.

```cpp
for(int i=1;i<d.size();i++){
	mail_id[d[i]] = id;
	mails[id].insert(d[i]);
}
```

--> And at last we will construct our ans vector.

Let's see final code:

```cpp
private:
	unordered_map<string,int>mail_id;
	vector<set<string>>mails;
	vector<string>name;
public:
vector<vector<string>> mergeDetails(vector<vector<string>>& details) {
	vector<vector<string>>ans;
	// Adding dummy values because we will start our id from 1.
	mails.push_back(set<string>());
	name.push_back("");
	for(auto &d:details){
		int id = 0;
		// check if any mail is already visited
		for(int i=1;i<d.size();i++){
			id = max(id,mail_id[d[i]]);
		}
		// If it's new
		if(id == 0){
			id = name.size();
			name.push_back(d[0]);
			mails.push_back(set<string>());
		}
		// set ids for all mails of their owner
		for(int i=1;i<d.size();i++){
			mail_id[d[i]] = id;
			mails[id].insert(d[i]);
		}
	}
	// Return answer
	for(int i=1;i<name.size();i++){
		ans.push_back({name[i]});
		for(auto &it:mails[i]){
			// our id is starting from 1 that's why we are doing this
			ans[i-1].push_back(it);
		}
	}
	// only for one test case on gfg
	sort(ans.rbegin(), ans.rend());
	return ans;
}
```

#unionfind #graph #DSU 

>[!tip]
>This is beautiful!
>```cpp
>// You can add code here also
>cout<<"segs"<<endl;
>```
