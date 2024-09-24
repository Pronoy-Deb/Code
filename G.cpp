#include <bits/stdc++.h>
#define int long long
#define ck(n) cout << #n " = " << n << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pe(c) for (auto& i : c) cout << i << ' '; cout << '\n'
#define pp(c) for (auto& [f, s] : c) cout << f << " : " << s << '\n'
#define pr(c) for (auto& i:c) {for (auto& j:i) cout<<j<<' '; cout<<'\n';}
#define pn(c, n) for (int i = 0; i < n; ++i) cout<<c[i]<<' '; cout<<'\n'
#define pc(t, n) cout << "Case " << t << ": " << n << '\n'
const int M = 1e9 + 7, N = 1e6 + 5;
using namespace std;
int ar[N], n;

void Accepted(int t) {
    // cin >> n;
    // for (int i = 0; i < n; ++i) { cin >> ar[i]; }
    string s; cin>>s;
    int w=0, ans=0;
    for(auto &i:s){
        if(i=='W') w++;
        else ans+=i-'0';
    }
    int n=s.size();
    cout<<n/6<<'.'<<n%6<<(((n/6>=1 and n%6>=1) or (n/6>=2))?(" Overs "):(" Over "))<<ans<<(ans>=2?" Runs ":" Run ")<<w<<(w>=2?(" Wickets."):(" Wicket."));
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 0, tc = 1;
    cin >> tc;
    while(t < tc) Accepted(++t);
    return 0;
}