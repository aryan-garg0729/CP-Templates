#include <bits/stdc++.h>
using namespace std;
/* sieve of Eretosthenes --> for N<=1000000 , queries<=1000000
   processing time:O(nloglogn) , extra space = O(n), answering query:O(1)
*/
#define MAX_N 1000001
vector<bool>isPrime(MAX_N,true);
void seive(){
    int n = MAX_N;
    isPrime[0] = isPrime[1] = false;
    for(int i = 2;i*i<=n;i++){
        if(isPrime[i]){
            for(int j = i*i;j<n;j+=i){
                isPrime[j] = false;
            }
        }
    }
    return;
}

// prime factorization in O(sqrt(n))
void PrimeFactorization(int N){
    for(int i = 2;i*i<=N;i++){
        while(N%i==0){
            cout<<i<<" ";
            N/=i;
        }
    }
    if(N!=1){
        cout<<N;
    }
}

// prime factorization of each query in O(logn) , preprocessing time O(nloglogn)
void AllPrimeFactors(int n) {
    //          preprocessing --> storing smallest prime factor of each number (1 to n)
	    vector<int>smallestPrimeDivisor(n+1);
	    for(int i = 0;i<n+1;i++){
	        smallestPrimeDivisor[i]=i;
	    }
	    
	    for(int i = 2;i*i<=n;i++){
	        if(smallestPrimeDivisor[i]==i){
	            for(int j =i*i;j<=n;j+=i){
	                if(smallestPrimeDivisor[j]==j){
	                    smallestPrimeDivisor[j] = i;
	                }
	            }
	        }
	    }

        // printing all prime factors of n in logn time. similarly answer any number of query
	    while(n!=1){
            cout<<smallestPrimeDivisor[n]<<" ";
	        n/=smallestPrimeDivisor[n];
	    }
	}

// segmented sieve --> print all numbers in range L,R (1<=L,R<=10^12 , R-L<=10^6)
vector<int> generatePrimes(int n){
    vector<int>primes;
    for(int i = 2;i<=n;i++){
        if(isPrime[i]){
            primes.push_back(i);
        }
    }
    return primes;
}
void segmentedSieve(){
    // generate all primes till 10^6 in isPrime array
    seive();

    int t;
    cin>>t;
    while(t--){
        int l,r;
        cin>>l>>r;

        // step 1: generate primes till sqrt(r) using isPrime array
        vector<int>primes = generatePrimes(sqrt(r));

        // step 2: dummy array of size r-l+1 and mark all true
        vector<bool>dummy(r-l+1,true);

        // step 3: mark all multiples of primes in dummy
        for(auto pr:primes){

            int firstMultiple = (l/pr)*pr;
            if(firstMultiple<l){
                firstMultiple+=pr;
            }

            for(int i = max(firstMultiple,pr*pr);i<=r;i+=pr){
                dummy[i-l] = false;
            }

        }
        if(l==1){
            dummy[0] = false;
        }

        // print answer
        for(int i = 0;i<r-l+1;i++){
            if(dummy[i]){
                cout<<i+l<<" ";
            }
        }
        cout<<endl;

    }
}

// x^n in O(logn) time
long long power(long long x,int n){
    long long res = 1;
    while(n){
        if(n%2!=0){
            res*=x;
            n--;
        }
        else{
            x *= x;
            n = n/2;
        }
    }
    return res;
}

// (x^n)%p in O(logn) time   n,p<=10^9  x<=10^18
long long BinModExp(long long x,int n,int p){
    x = x%p; // to handle x<=10^18
    long long res = 1;
    while(n){
        if(n&1!=0){  //n is odd
            res = (res*x)%p;
            n--;
        }
        else{
            x = (x*x)%p;
            n = n/2;
        }
    }
    return res;
}

// (x^n)%p in O(logn) time   n<=10^9  p,x<=10^18









#define M 1000000007
vector<vector<long long>> matMul(vector<vector<long long>>a, vector<vector<long long>>b){
    vector<vector<long long>>ans(a.size(),vector<long long>(b[0].size(),0));
    for(int i = 0;i<a.size();i++){
        for(int j = 0;j<b[0].size();j++){
            for(int k = 0;k<b.size();k++){
                ans[i][j] += (a[i][k]*b[k][j])%M;
                ans[i][j]%=M;
            }
        }
    }
    return ans;
}
vector<vector<long long>> binaryMatExp( vector<vector<long long>>a,int n){
    int l = 2;
    if(n==0){
        // return identity mat
        vector<vector<long long>>ans(l,vector<long long>(l,0));
        for(int i = 0;i<l;i++){
            ans[i][i] = 1;
        }
        return ans;
    }
    if(n==1){
        return a;
    }
    vector<vector<long long>>ans = binaryMatExp(a,n/2);
    ans = matMul(ans,ans);
    if(n%2==0){
        return ans;
    }
    return matMul(ans,a);
}

int main(){
    // AllPrimeFactors(100235460);
    // cout<<endl;
    // PrimeFactorization(100235460);
    // segmentedSieve();
    // cout<<BinExp(2,1000000000,1000000007);
    long long n;
    cin>>n;
    vector<vector<long long>>mat = {{2,0},{1,4}};
    vector<vector<long long>>b = {{3,4}};

    mat = binaryMatExp(mat,n-1);
    b = matMul(b,mat);
    cout<<b[0][0]%M<<endl;
    return 0;
}