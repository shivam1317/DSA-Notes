## Problem:

> Given a 2d list that represents the nodes of a [Binary tree](https://www.geeksforgeeks.org/binary-tree-data-structure/) with **N** nodes, the task is to find the maximum [GCD](https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/) of the siblings of this tree without actually constructing it.  
> **Note:** If there are no pairs of siblings in the given tree, print 0. Also, if given that there's an edge between a and b in the form of {a,b} in the list, then a is the parent node.

## Example:

**Input:**

```
N = 7
arr = {{4, 5}, {4, 2}, {2, 3}, {2, 1}, {3, 6}, {3, 12}}
```

**Output:**

```
6
```

**Explanation:**
![](../GFG/Attachments/Pasted%20image%2020220525175202.png)

```
For the above tree, the maximum GCD for the sibilings is 6, formed for the nodes 6 and 12 for the children of node 3.
```

## Approach:

--> Here we will sort the array first so that `nodes with same parent` will come after each other and then we will simply check if their parent is same then we will find gcd of them.

### Base case

--> One base case is `when there is no sibilings or there is only 1 node in tree` then we will just check like this:

```cpp
if(arr.size() == 0){
	return 0;
}
```

--> If it's not 0 then we will run this logic.

```cpp
// Function to find GCD
int gcd(int a,int b){
        while(b != 0){
            int rem = a%b;
            a = b;
            b = rem;
        }
        return a;
    }
    int maxBinTreeGCD(vector<vector<int>> arr, int N) {
        if(arr.size() == 0){
            return 0;
        }
        sort(arr.begin(),arr.end());
		// maxi will store our ans
        int maxi = 0;
        for(int i=0;i<arr.size()-1;i++){
            if(arr[i][0] == arr[i+1][0]){
                maxi = max(maxi,gcd(arr[i][1],arr[i+1][1]));
            }
        }
        return maxi;
    }
```
