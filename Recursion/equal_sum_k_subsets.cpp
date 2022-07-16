//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
/*You are required to complete this method */

class Solution{
  public:
    bool solve(int idx,int tempsum,int target,int n,int k,int a[],vector<bool>  &vis){
        if(k==1) return true; // if reducing till 1 gives true that means we have found k-1 subsets with target sum then we will return true
        if(tempsum>target) return false;
        if(tempsum = target) return solve(0,0,target,n,k-1,a,vis); // if we find one subset with target sum then we will check for remaining k
        for(int i=idx;i<n;i++){
            // we wil proceed if that element is unvisited or not included in other subset
            if(vis[i]==false){
                if(solve(i+1,tempsum+a[i],target,n,k,a,vis)) return true; // checks if next element should be added in subset or not
                else vis[i] = false;
            }
        }
        return false; // if no subsets found with target sum then return false
    }
    bool isKPartitionPossible(int a[], int n, int k)
    {
         //Your code here
         int sum=0;
         for(int i=0;i<n;i++){
            sum += a[i];
         }
         if(k==1) return true;
         if(k==0 || k>n || sum%k!=0) return false;
         vector<bool>vis(n,false);
         int target = sum/k;
         return solve(0,0,target,n,k,a,vis); // solve(idx,tempsum,target,no_of_eles,no_of_subsets,given_arr,vis_arr)
         // tempsum -> total sum of individual element with others like sum of 2(first ele) with remaining ele this will resent if we jump to next element of array
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    	int n;
    	
    	cin>>n;
    	int a[n];
    	for(int i=0;i<n;i++)
    	cin>>a[i];
    	int k;
    	cin>>k;
    	Solution obj;
    	cout<<obj.isKPartitionPossible(a, n, k)<<endl;
    }
}
// } Driver Code Ends
