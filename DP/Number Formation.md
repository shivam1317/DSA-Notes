>[!Problem Statement]
>Given three integers **x, y,** and **z,** the task is to find the sum of all the numbers formed by having 4 at most x times, having 5 at most y times, and having 6 at most z times as a digit.

## Example

**Input**: 
```
X = 1, Y = 1, Z = 1 
```
**Output:** 
```
3675
```
**Explanation**: 
```
4 + 5 + 6 + 45 + 54 + 56 + 65 + 46 + 64 + 456 + 465 + 546 + 564 + 645 + 654 = 3675
```

## Approach:

--> here we have to find all the combinations of `4,5 and 6` and then sum them together. For that we can think in another way that we will try all the combinations of values of `X,Y and Z` and then find answer for the **exact values of `X,Y and Z`** and then sum them all. this thing leads to subproblems solving and we know best thing to handle this which is `DP`.

so we will store this answers of these subproblems in our DP array and then using these answers we will solve another subproblems.

For example we have to find the sum of numbers for exact values of `X,Y and Z` as `1,1,0` then we have to first find the sum for `1,0,0` and then `0,1,0` so for `1,0,0` the answer will be `4` and for `0,1,0` the answer will be `5` and after that we will append `5` to `4` (for 1,0,0) and we will append `4` to `5`(for 0,1,0) and we can do this with below formula:

```
new_number = (sum)*10 + (number_to_append)*(count_of_number)
new_number = (4)*10 + (5)*(1)
new_number = 40+5 = 45
```

### Why we need count_of_number?

--> Because we can have more than 1 count which we have to append in sum. for example, we want to append `two 4s` in sum of 15 then `wherever we will put these two 4s, the sum will be always same` so we will just add `4*2` in previous sum by multiplying previous sum with 10 (as per above formula).

--> Like this, we will find sums for all combinations of `X,Y and Z` and then add them in our final answer and return it.

## Base case:

--> If all `X,Y and Z` all are 0 then we have to set their count as `1` because if we don't do that then we will get 0 as final answer.

```cpp
nums[0][0][0] = 1;
```

### We will need this things:

```
1. exactSum 3D array (which is dp array) initialised with 0
2. nums 3D array (which will store number of digits used to form previous sum) initialised with 0
3. ans (which will store our final sum)
```

--> Let's see the code:

## Code:
```cpp
int getSum(int X, int Y, int Z) {
        vector<vector<vector<long long>>>exactSum(X+1,vector<vector<long long>>(Y+1,vector<long long>(Z+1,0)));
        vector<vector<vector<long long>>>nums(X+1,vector<vector<long long>>(Y+1,vector<long long>(Z+1,0)));
        // base case
        nums[0][0][0] = 1;
        long long ans = 0;
        int mod = 1000000007;
        for(int i=0;i<=X;i++){
            for(int j=0;j<=Y;j++){
                for(int k=0;k<=Z;k++){
                    if(i>0){
                        exactSum[i][j][k] += ((exactSum[i-1][j][k])*10 + 4*(nums[i-1][j][k]))%mod;
                        // adding digits used to form the previous sum
                        nums[i][j][k] += nums[i-1][j][k]%mod;
                    }
                    if(j>0){
                        exactSum[i][j][k] += ((exactSum[i][j-1][k])*10 + 5*(nums[i][j-1][k]))%mod;
                        nums[i][j][k] += nums[i][j-1][k]%mod;
                    }
                    if(k>0){
                        exactSum[i][j][k] += ((exactSum[i][j][k-1])*10 + 6*(nums[i][j][k-1]))%mod;
                        nums[i][j][k] += nums[i][j][k-1]%mod;
                    }
                    ans += exactSum[i][j][k]%mod;
                    ans%=mod;
                }
            }
        }
        return (int)ans;
    }
```

#dp #tabulation 