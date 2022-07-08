## Problem Statement:

> Given **N** Magnets which are placed linearly, with each magnet to be considered as of point object. Each magnet suffers force from its left sided magnets such that they repel it to the right and vice versa. **All forces are repulsive**. The force being equal to the distance (1/d , d being the distance). Now given the positions of the magnets, the task to find all the points along the linear line where net force is **ZERO**.

> More Formally, Magnets are placed on X axis, the coordinates of which are given, you are asked to find out the X-co-ordinates of all the equilibrium points (i.e. the point where net force is zero). You notice the point each magnet repels each other, it means the polarity of the magnet is such that exerts +ve force in its right side and -ve force in left side, (here +ve is considered in +ve direction of x-axis). And that forces are inversely proportional to the distance, thus there lies an equilibrium point between every two magnetic points. Thus there will be total of **N-1** equllibrium points. You have to find those N-1 points.  
> **Note:** Array **M[]** is **sorted** and distance have to be calculated with precision of **2 decimal places**.

## Example:

**Input:**

```
N = 4
M[] = {0, 10, 20, 30}
```

**Output:**

```
3.82, 15.00, 26.18
```

## Approach:

--> Now here we have n magnets placed in row and each magnet is giving `1/d` force on both left and right side. and if one magnet is at some point in array then ofcourse it will get force from all it's right elements to the left side and same for right side so we just have to find the point where the left force and right force becomes same for any point between `arr[i] and arr[i+1]`.

--> So in above problem first we have to find equillibrium point between `0 and 10` so we will use `binary search` here. we will make 0 as `left` and `10` as right and their `mid` will be 5.

==> So if we count the `Force by all right elements to the left side` then it will be

```
1/(10-5) + 1/(20-5) + 1/(30-5) = 0.306
```

Now if we count `Force by all left elements to the right` then it will be

```
1/(5-0) = 0.25
```

### Diagram:

![](../GFG/Attachments/Pasted%20image%2020220612003635.png)

So here we can see the force to the right side is lower so we will goto left side `so that we can get bigger divider value` by doing `Right=mid`

And if the force to the left side is greater than force to the right side then we will goto `right side` by doing `left=mid`

--> So we will follow this process for each element and if we find both right and left forces same then we will make `mid` as answer for that element.

### Diagram

![](../GFG/Attachments/Pasted%20image%2020220612004329.png)

## Code:

```cpp
// Force by right magnets to the left side
    double CalcLeftForce(double magnets[],int i,int n,double mid){
        double leftForce = 0;
        for(int j=i;j<n;j++){
            leftForce += 1/(magnets[j]-mid);
        }
        return leftForce;
    }
    // Force by left magnets to the right side
    double CalcRightForce(double magnets[],int i,int n,double mid){
        double rightForce = 0;
        for(int j=i-1;j>=0;j--){
            rightForce += 1/(mid-magnets[j]);
        }
        return rightForce;
    }
    void nullPoints(int n, double magnets[], double getAnswer[])
    {
        for(int i=0;i<n-1;i++){
            double left = magnets[i];
            double right = magnets[i+1];
            double mid = left;
            while(left <= right){
                mid = left + (right-left)/2;
                double leftForce = CalcLeftForce(magnets,i,n,mid);
                double rightForce = CalcRightForce(magnets,i,n,mid);
                if(abs(leftForce-rightForce) < 0.000001){
                    break;
                }
                else if(leftForce < rightForce){
                    left = mid;
                }else{
                    right = mid;
                }
            }
			// Making mid as our answer because that's the equillibrium point
            getAnswer[i] = mid;
        }
    }
```
