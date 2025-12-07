#include <bits/stdc++.h>
using namespace std;

int editCost(const string &s, const string &t, int ins, int del, int rep) {
    int n = s.size(), m = t.size();
    vector<int> dp(m+1), ndp(m+1);
    for(int j=0;j<=m;j++) dp[j] = j*ins;
    for(int i=1;i<=n;i++){
        ndp[0] = i*del;
        for(int j=1;j<=m;j++){
            int cost_del = dp[j] + del;
            int cost_ins = ndp[j-1] + ins;
            int cost_rep = dp[j-1] + (s[i-1]==t[j-1]?0:rep);
            ndp[j] = min({cost_del, cost_ins, cost_rep});
        }
        dp = ndp;
    }
    return dp[m];
}

void palindromeFactory() {
    int T; cin >> T;
    while(T--){
        string s; int k, ins, del, rep;
        cin >> s >> k >> ins >> del >> rep;

        vector<int> freq(26,0);
        for(char c:s) freq[c-'a']++;

        vector<int> letters;
        for(int i=0;i<26;i++) if(freq[i]>0) letters.push_back(i);

        int ans = INT_MAX;
        int d = letters.size();

        for(int mask=1; mask<(1<<d); mask++){
            vector<char> chosen;
            for(int i=0;i<d;i++) 
                if(mask&(1<<i)) chosen.push_back('a'+letters[i]);

            vector<char> middles;
            if(k%2) middles = chosen;
            else middles.push_back(0);

            for(char mid:middles){
                string half="";
                for(char c:chosen) half += string(k/2, c);

                string middle="";
                if(mid) middle = string(1, mid);

                string full = half + middle;
                string half_rev = half; reverse(half_rev.begin(), half_rev.end());
                full += half_rev;

                ans = min(ans, editCost(s, full, ins, del, rep));
            }
        }
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    palindromeFactory();
}
