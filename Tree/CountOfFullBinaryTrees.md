>[!Problem Statement]
>Given an array **arr[]** of **n** integers, where each integer is greater than 1. The task is to find the number of [Full binary tree](http://quiz.geeksforgeeks.org/binary-tree-set-3-types-of-binary-tree/) from the given integers, such that each non-leaf node value is the product of its children value.
>**Note:** Each integer can be used multiple times in a full binary tree. The answer can be large, return  answer modulo 1000000007

## Example:

**Input:**
```
n = 4
arr[] = {2, 3, 4, 6}
```
**Output:**
```
7
```
**Explanation:**
```
There are 7 full binary tree with
the given product property.
Four trees with single nodes
2  3  4  6
Three trees with three nodes
    4   
   / \
  2   2 ,
   6    
  / \
 2   3 ,
   6
  / \
 3   2
```

## Approach:

--> Here from question we can make one observation which is, `we only have to consider non-prime numbers` so that we can find it's any 2 factors and add it's all combinations in our final ans.

Also we know one thing that all individual elements will also make one full binary tree so we have to consider that also.

--> So now for each element, we will run one inner for loop to consider it's all multiples and we will add them in our ans.

>Also we have to make a check for elements which are in our array because we are running outer loop from min to max value.
>And we can check this using `temp` array which will have initial value as `0` for elements which are not into the array.

For example if we are considering `6` then there can be 2 possiblities:

```
6 have 2 at left and 3 at right
6 have 3 at left and 2 at right
```

So to encounter this problem, we will add one more condition in our inner for loop which will be `j/num <= num where j will be iterator for inner loop and num will be iterator for outer loop`. So for `num=2` we will not consider 6 because `6/2>3` and for `num=3 we will consider 6 because 6/3 <= 3`

### How we will find all possibilites for given number?

For exmaple, we are checking the factors of 2 and we have an element 10 then we have to add it's all possibilites which will be equal to `possibilities using 2 * possibilites using 10/2`

But there is an one edge case which is when both factors of any number are same then we will consider it only once.

## Final code:

```cpp
long long int numoffbt(long long int arr[], int n){
        long long int mini = INT_MAX;
        // we don't need to initialse maxi to INT_MIN because all values will be less than 1
        long long int maxi = 1;
        for(int i=0;i<n;i++){
            mini = min(mini,arr[i]);
            maxi = max(maxi,arr[i]);
        }
        vector<int>temp(maxi+1,0);
        long long int ans = 0;
        int mod = 1000000007;
        for(long long i=0;i<n;i++){
            temp[arr[i]] = 1;
        }
        for(long long int num=mini;num<=maxi;num++){
            if(temp[num] != 0){
                for(long long int j=num+num;j<=maxi && j/num <= num;j+=num){
	                // we also have to check if current multiple is in array or not
                    if(temp[j] != 0){
                         temp[j] += (temp[num])*(temp[j/num]);
                         if(num != j/num){
                             temp[j] += (temp[num])*(temp[j/num]);
                         }
                    }
                   
                }
                // If you do ans += temp[num]%mod then it will give wrong ans because we are doing mod here so it's recommended to take ans+temp[num] and mod it and then again add it in ans.
                ans = (ans + temp[num])%mod;
            }
        }
        return ans;
    }
```

#Array #tree #prime-numbers  