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
