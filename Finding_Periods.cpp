#include<bits/stdc++.h>
using namespace std;


// #define int long long
#define pb push_back
#define F first
#define S second

// const int inf = 1LL<<62;
const int md = 1000000007;

void z(string s) {
    int n = s.size();
    vector<int> z(n,0);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0,min(z[i-x], y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i; y = i + z[i]; z[i]++;
        }
        if (z[i] + i == n) cout<<i<<' ';
    }
    cout<<n;
}
void solve(){
    string s; cin>>s;
    z(s);
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t=1;
    //cin>>t;
    for (int i = 1; i <= t; i++) {
        solve();
        cout<<'\n';
    }
}