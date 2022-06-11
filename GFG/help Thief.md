## Problem:

>You have to help a thief to steal as many as GoldCoins as possible from a GoldMine. There he saw **N** Gold Boxes an each Gold Boxes consists of **Ai** Plates each plates consists of **Bi** Gold Coins. Your task is to print the maximum gold coins theif can steal if he can take a maximum of T plates.

## Example:

**Input:**
```
T=3, N=3 
A[]={1, 2, 3}
B[] ={3, 2, 1}
```
**Output:**
```
7
```
**Explanation:**
```
The thief will take 1 plate of coins from the first box and 2 plate of coins from the second plate. 3 + 2*2 = 7.
```

## Approach:

--> Here we can take as many boxes we can take as we want from total of A[i] boxes. So if there are 3 boxes and each box have 6 gold then we can also take 2 boxes which will be total 12gold or we can take all 3 boxes which will have total 18 gold.

--> So the above explaination direct us to a greedy solution so we can `Sort the B[] array in descending order` and then take the boxes till `T` becomes 0.

### Now here we have to keep 2 things in mind:

1. If T is greater than B[i] then add A[i]*B[i] in our answer.
2. If T is smaller than or equal to B[i] then add T*B[i] in our answer because we want as max as possible gold.

## Code:

```cpp
	static bool cmp(pair<int,int>&a,pair<int,int>&b){
      	return a.second > b.second;
  	}
    int maxCoins(int A[], int B[], int T, int N) {
        int ans = 0;
        vector<pair<int,int>>v;
        for(int i=0;i<N;i++){
            v.push_back(make_pair(A[i],B[i]));
        }
        sort(v.begin(),v.end(),cmp);
        for(int i=0;i<N;i++){
            if(T - v[i].first > 0){
                ans += v[i].first*v[i].second;
                T -= v[i].first;
            }
            else{
                ans += T*v[i].second;
                break;
            }
        }
        return ans;
    }
```