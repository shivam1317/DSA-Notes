## Problem:

>Geek is organising a bike race with N bikers. The initial speed of the ith biker is denoted by Hi Km/hr and the acceleration of ith biker as Ai Km/Hr2. A biker whose speed is 'L' or more, is considered be a fast biker. The total speed on the track for every hour is calculated by adding the speed of each fast biker in that hour. When the total speed on the track is 'M' kilometers per hour or more, the safety alarm turns on.   
Find the minimum number of hours after which the safety alarm will start.

## Example:

**Input:**
```
N = 3, M = 400, L = 120
H = {20, 50, 20}
A = {20, 70, 90}
```
**Output:** 
```
3
```
**Explaination:** 
```
Speeds of all the Bikers at ith hour
Biker1= [20  40  60  80 100] 
Biker2= [50 120 190 260 330]
Biker3= [20 110 200 290 380] 

Initial Speed on track  = 0 
because none of the biker's speed is fast enough.
Speed on track after 1st Hour= 120
Speed on track after 2nd Hour= 190+200=390
Speed on track after 3rd Hour= 260+290=550
Alarm will start at 3rd Hour.
```

## Approach:

--> The initial or native approach will be to `Store speed in a array after every hour` and during adding the speed in array check `If that speed is greater than L` and if it's greater than L then add it into `tempSum` and after adding every bike's speed check `If tempSum is greater than M or not` and if it's greater than `M` then break the while loop and return the ans which will be our counter after every loop.

## Brute Force Code:

```cpp
long buzzTime(long N, long M, long L, long H[], long A[])
    {
        vector<long>helper(N,0);
        for(long i=0;i<N;i++){
            helper[i] += H[i];
        }
        long long tempSum = 0;
        long ans = -1;
        bool flag = false;
        
        while(!flag){
            for(long i=0;i<N;i++){
                if(helper[i] >= L){
                    tempSum += helper[i];
                }
                if(tempSum >= M){
                    flag = true;
                    break;
                }
                helper[i] += A[i];
            }
            ans++;
            tempSum = 0;
        }
        return ans;
    }
```

The above code will give `TLE` so we have to optimise it!

--> Because the above code will learn for every single hour and we are linearly increasing `ans` variable by `1`.

### so why don't we use `Binary Search Here`? 
we will make 2 variables `low and high`. low will be `0` and high will be `M` at start and then we will find `mid` and Current speed for that hour will be `H[i] + (A[i]*mid)` because we are treating `mid` as a hour.

--> Now using this mid variable, we will check if we are getting our ans means `The totalSum is greater than or equal to M` and if it returns true then we will goto mid's left side means now our `high will become mid` because we want the `minimum number of hours`

## Binary search code:

```cpp
bool check(int T,int N,int M,int L,long H[],long A[]){
        long tempSum = 0;
		// find speed for Tth our and add in tempSum if it's greater than or equal to L
        for(long i=0;i<N;i++){
            long speed = H[i] + (A[i]*T);
            if(speed >= L){
                tempSum += speed;
            }
        }
	// Return if tempSum is greater than or equal to M or not.
        return tempSum >= M;
    }
    long buzzTime(long N, long M, long L, long H[], long A[])
    {
        long low = 0,high = M;
        
        while(low < high){
            long mid = low + (high-low)/2;
			// If mid gives ans then goto left means lower side of mid to get smallest ans
            if(check(mid,N,M,L,H,A)){
                high = mid;
			// If mid don't gives ans then goto right or greater side of mid
            }else{
                low = mid+1;
            }
        }
        return high;
    }
```