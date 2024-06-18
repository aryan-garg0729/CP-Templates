#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Stable, not inplace, tc=O(d*(n+b)) (b is base, d in max # digits, n is input length) | sc=O(n+b)
void radixSort(vector<int> &nums){
    // Write your code here.
    if (nums.size() == 0)return;
    
    int maxi = *max_element(nums.begin(), nums.end());
    int digits = 0;
    // counting maximum # digits in any number
    while (maxi != 0){
        digits++;
        maxi /= 10;
    }
    int n = nums.size();

    vector<int> sorted(n, 0);
    vector<int> count(10, 0);
    // sorting all digits from lsd to msd
    for (int i = 1; i <= digits; i++){
        // filling count array
        for (int j = 0; j < n; j++){
            int curr = nums[j] / pow(10, i - 1);
            count[curr % 10]++;
        }

        // prefix sum of count array to find correct indexes 
        for (int j = 1; j < 10; j++){
            count[j] += count[j - 1];
        }

        // putting numbers to their indexes sorted as per ith digit
        for (int j = n - 1; j >= 0; j--){
            int curr = nums[j] / pow(10, i - 1);
            curr %= 10;
            count[curr]--;
            sorted[count[curr]] = nums[j];
        }
        nums = sorted;
        for (int j = 0; j < 10; j++)
            count[j] = 0;
    }
    return;
}


//  	                Count Inversions in nlogn (using merge sort)
long long merge(vector<long long>&nums,long long s1,long long e1,long long s2,long long e2){
    vector<long long>a(e2-s1+1);
    long long ans = 0;
    long long i=0,p1=s1,p2=s2;
    while(p1<=e1 && p2<=e2){
        if(nums[p1]<=nums[p2]){
            a[i]=nums[p1];
            p1++;
        }
        else{
            a[i]=nums[p2];
            ans+=(e1-p1+1);
            p2++;
        }
        i++;
    }
    while(p1<=e1){
        a[i] = nums[p1];
        p1++;
        i++;
    }
    while(p2<=e2){
        a[i] = nums[p2];
        p2++;
        i++;
    }
    for(long long i = s1;i<=e2;i++){
        nums[i] = a[i-s1];
    }
    return ans;
}
long long countInversion(vector<long long>&nums,long long s,long long e){
    if(s>=e)return 0;
    long long mid = (s+e)/2;
    return countInversion(nums,s,mid)+countInversion(nums,mid+1,e)+merge(nums,s,mid,mid+1,e);
}
long long countInversions(vector<long long> &nums) {
    return countInversion(nums,0,nums.size()-1);
}