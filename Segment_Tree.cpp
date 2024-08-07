#include <bits/stdc++.h>
using namespace std;

class SegmentTree{
    vector<long long>seg;
    int n;
    void build(vector<int>&nums,int ind,int low, int high){
        if(low==high){
            seg[ind] = nums[low];
            return;
        }
        int mid = (low+high)/2;
        build(nums,2*ind+1,low,mid);
        build(nums,2*ind+2,mid+1,high);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }
    long long query(int ind,int low,int high,int l,int r){
        // no overlap
        if(l>high || r<low)return 0;

        // complete overlap
        if(low>=l && high<=r) return seg[ind];

        // partial overlap
        int mid = (low+high)/2;
        long long left = query(2*ind+1,low,mid,l,r);
        long long right = query(2*ind+2,mid+1,high,l,r);
        return left+right;
    }

    void update(int ind,int low,int high,int i,int val){
        if(low==high){
            seg[ind] = val;
            return;
        }

        int mid = (low+high)/2;
        
        if(mid>=i)update(2*ind+1,low,mid,i,val);
        else update(2*ind+2,mid+1,high,i,val);

        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }

    public:
    SegmentTree(vector<int>&nums,int val){
        n = nums.size();
        seg.resize(4*n,val);
        build(nums,0,0,n-1);
    }
    
    // query range l to r
    long long query(int l,int r){
        return query(0,0,n-1,l,r);
    }

    // point update(replace value at index i with val)
    void update(int ind,int val){
        update(0,0,n-1,ind,val);
    }
    
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    vector<int>nums(n);
    for(int i = 0;i<n;i++){
        cin>>nums[i];
    }
    SegmentTree seg(nums,0);
    for(int i = 0;i<q;i++){
        int type,l,r;
        cin>>type>>l>>r;
        l--;
        if(type==1){
            seg.update(l,r);
        }
        else {
            r--;
            cout<<seg.query(l,r)<<endl;
        }
    }
    return 0;
}


