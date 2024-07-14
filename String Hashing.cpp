class Hash{
    vector<pair<long long, long long>> prefixHash; 
    vector<pair<long long, long long>> powers; 
    const int BASE1; 
    const int BASE2;
    int mod; 
    public:
    Hash(string str):BASE1(4691),BASE2(7591){
        mod = 1e9 + 7;
        prefixHash.resize(str.size() + 1, {0, 0});
        powers.resize(str.size() + 1, {1, 1});
        // precompute powers 
        for (int i = 1; i < str.size(); i++){
            powers[i] = {
                (powers[i - 1].first * BASE1)%mod, 
                (powers[i - 1].second * BASE2)%mod
            };
        }
        // compute prefixhash
        for (int i = 1; i <= str.size(); i++){
            int ind = i - 1; 
            prefixHash[i] = {
                (1ll*prefixHash[i - 1].first * BASE1 + (str[ind] - 'a' + 1)) %mod, 
                (1ll*prefixHash[i - 1].second * BASE2 + (str[ind] - 'a' + 1)) %mod
            };
        }
    }

    pair<int, int> getHash(int left, int right){
        left++; 
        right++; 
        return {(prefixHash[right].first - (prefixHash[left - 1].first * powers[right - left + 1].first) % mod + mod) % mod, 
                (prefixHash[right].second - (prefixHash[left - 1].second * powers[right - left + 1].second) % mod + mod) % mod};
    }

};