## problem:

>Given a binary matrix **M** with **R** rows and **C** columns, where each element of the matrix will be 0 or 1. Find the largest square that can be formed with center **(i, j)** and contains atmost **K** 1s. There are Q queries, a single query has two integers denoting the centre (i,j) of the square.

## Example:

**Input:**
```
R = 4, C = 5
M = {{1, 0, 1, 0, 0} 
     {1, 0, 1, 1, 1} 
     {1, 1, 1, 1, 1} 
     {1, 0, 0, 1, 0}}
K = 9, Q = 1
q_i[] = {1}
q_j[] = {2}
```
**Output:**
```
3
```
**Explanation:**
```
Maximum length square with center at (1, 2) that can be formed is of 3 length from (0, 1) to (2, 3).
```

--> Diagram for above testcase:

![](../GFG/Attachments/Pasted%20image%2020220720143934.png)

## Understanding question in more detail:

--> So here we have to find the `maximum length of square` which have q_i and q_j elements as center. i.e we will take one element at a time from q_i and q_j (let's call it i and j) and then goto that index and then try to make center by making `(i,j)` center and `it must have at most k 1s`.

## Approach:

--> So first we have to find out the maximum time we can expand our square (i.e the max length of square) we can make by taking `(i,j)` as center. so to find that first we have to find `no of rows above, no of rows below,no of columns to the right and no of columns to the left of current cell.`

So it will look like this for previous example:

![](../GFG/Attachments/Pasted%20image%2020220720145551.png)

--> Now we know that in square, the length of all sides is same that's why we will take `minimum` of all these values and that will be `the maximum times we can expand our square`. 

so here we can only expand `1` times.

Now let's see for this example:

![](../GFG/Attachments/Pasted%20image%2020220720150412.png)

Here `0` means we can't expand more so max square length will be `1`. 

>Remember that each separate cell is also a square with length 1.

--> Now to find the square length on the basis of no of times we can expand, we will use this formula:

```
square length = no of expand in both sides + 1
square length = 2* no expand + 1
// we are taking 1 for current row
```

So if we can expand our square `1` times then maximum square size will be :

```
= 2*1 + 1
= 3
```

So our final formula is :

```
2*ex+1 where ex is max number of expanding 
```

### But this square must have at most k 1s

--> To tackle this condition, we will start by `expanding the square one by one` and after each expand we will find the number of `1s` in that submatrix and if it's less than `k` then we will expand more but if it's greater than `k` then we will break and then we will find the length of that submatrix.

>Our loop will run from 0 to max number of expanding

--> It will look like this in code:

```cpp
vector<int> largestSquare(vector<vector<int>> M, int R, int C, int K, int Q, int q_i[], int q_j[]) {
        vector<int>ans;
        // Running loop for each query
        for(int q=0;q<Q;q++){
            int i = q_i[q];
            int j = q_j[q];
            // max Squre size can be formed = min(min(up,down),min(left,right))
            // finding max expanding
            int min_dist = min(min(i,R-i-1),min(j,C-j-1));
            int maxSize = 0;
            // running loop from 0 to max_expanding
            for(int ex=0;ex<=min_dist;ex++){
                int count = 0;
                // finding count of 1s in current submatrix
                for(int row=i-ex;row<=i+ex;row++){
                    for(int col=j-ex;col<=j+ex;col++){
                        if(M[row][col] == 1){
                            count++;
                        }
                    }
                }
                if(count <= K){
                    maxSize = 2*ex+1;
                }else{
                    break;
                }
            }
            ans.push_back(maxSize);
        }
        return ans;
    }
```

--> Now this code will pass all the `base test cases` but it will give `TLE` for some test cases because we are running 2 for loops for only finding `1s` in the submatrix so we need to optimise it.

==> So why don't we store the counts in `dp array` here? 😏

## DP solution (Efficient)

--> So first we will store the count of 1s in dp array. `dp[i][j] will store the count of 1s in submatrix from (0,0) to (i,j)`. 

![](../GFG/Attachments/Pasted%20image%2020220720160857.png)

--> Now for first row and column we will count the number of 1s like we count in prefix sum. 

Diagram:

![](../GFG/Attachments/Pasted%20image%2020220720161343.png)

## Code:

```cpp
dp[0][0] = M[0][0];
// first row
for(int i=1;i<R;i++){
    dp[i][0] = M[i][0] + dp[i-1][0];
}
// first column
for(int j=1;j<C;j++){
	dp[0][j] = M[0][j] + dp[0][j-1];
}
```

--> now for remaining cells we will take the number of 1s till it's previous row and number of 1s till it's previous column and we will add them. 

Also we have to consider current cell also.

```
M[i][j] + dp[i-1][j] + dp[i][j-1]
```

Now if we take a look at any example:

![](../GFG/Attachments/Pasted%20image%2020220720162136.png)

So here we can see for `(1,1)` ,`dp[0][1]+dp[1][0]` is `3` but correct answer should be `2` and we are getting 3 because it's adding the `1 at index (0,0)` 2 times. and we will get this problem for each cell so we just have to `subtract dp[i-1][j-1]` to get correct ans.

So our final equation will be:

```
dp[i][j] = M[i][j] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
```

--> Now we have initialised our dp array but still there is one problem 😔

Now if we want the number of 1s in any submatrix which is starting from `(0,0)` and ending at any `(i,j)` then we can easily get it from dp array.

### But what if we want the number of 1s in any submatrix which is not starting from (0,0) 🤔?

then again we have to do some maths 😎.

--> Now suppose we want to find the number of 1s in the submatrix shown in diagram:

![](../GFG/Attachments/Pasted%20image%2020220720170413.png)

--> So first we have to find the count of all 1s in matrix till that `(i,j)` and then subtract the other part's value which is not in our submatrix.

See diagram for more clearity:

![](../GFG/Attachments/Pasted%20image%2020220720171157.png)

--> Now suppose we are at `k`th expanding and current indexes are `i and j` so the total number of 1s till current square will be `dp[i+k][j+k]` and now we have to subtract the highlighted part from this value.

The number of 1s in blue highlighted part will be in `dp[i+k][j-k-1]` so we have to subtract it from total number of 1s

So our current equation will be:

```
dp[i+k][j+k]-dp[i+k][j-k-1]
```

--> Now we are left with this part shown in diagram below:

![](../GFG/Attachments/Pasted%20image%2020220720171854.png)

--> Now we want to remove the above part so we will take the number of 1s in above part and we can get it by going to previous row in same last column which will be `dp[i-k-1][j+k]`.

![](../GFG/Attachments/Pasted%20image%2020220720172219.png)

--> Now we have to subtract this also from our total number of counts so now our equation will be :

```
dp[i+k][j+k]-dp[i+k][j-k-1]-dp[i-k-1][j+k]
```

But we can see that we have subtracted the left above part 2 times so we have to add it again 1 time in our equation:

```
dp[i+k][j+k]-dp[i+k][j-k-1]-dp[i-k-1][j+k]+dp[i-k-1][j-k-1]
```

So let's see this dp part in code:

## Final code:

```cpp
vector<int> largestSquare(vector<vector<int>> M, int R, int C, int K, int Q, int q_i[], int q_j[]) {
		// It will store our answer
        vector<int>ans;
        vector<vector<int>>dp(R,vector<int>(C));
        dp[0][0] = M[0][0];
        // first row
        for(int i=1;i<R;i++){
            dp[i][0] = M[i][0] + dp[i-1][0];
        }
        // second row
        for(int j=1;j<C;j++){
            dp[0][j] = M[0][j] + dp[0][j-1];
        }
        // remaining cells
        for(int i=1;i<R;i++){
            for(int j=1;j<C;j++){
                dp[i][j] = M[i][j] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
            }
        }
        // going for each query
        for(int q=0;q<Q;q++){
            int i = q_i[q];
            int j = q_j[q];
            // max Squre size can be formed = min(min(up,down),min(left,right))
            int min_dist = min(min(i,R-i-1),min(j,C-j-1));
            int maxSize = 0;
            for(int ex=0;ex<=min_dist;ex++){
                int count = 0;
                int x1 = i-ex;
                int y1 = j-ex;
                int x2 = i+ex;
                int y2 = j+ex;
                // Formula: dp[i+k][j+k]-dp[i+k][j-k-1]-dp[i-k-1][j+k]+dp[i-k-1][j-k-1]
                count += dp[x2][y2];
                // we have to check out of bound conditions also that's why i have written this if statements
                if(y1 > 0){
                    count -= dp[x2][y1-1];
                }
                if(x1 > 0){
                    count -= dp[x1-1][y2];
                }
                if(x1 > 0 && y1 > 0){
                    count += dp[x1-1][y1-1];
                }
                if(count <= K){
                    maxSize = 2*ex+1;
                }else{
                    break;
                }
            }
            ans.push_back(maxSize);
        }
        return ans;
    }
```

--> And this code will pass every test case 😎🤝