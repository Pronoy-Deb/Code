#include <bits/stdc++.h>
#define int long long
#define ck(n) cout << #n " = " << n << '\n'
#define ps(b) cout << (b ? "YES" : "NO") << '\n'
#define pe(c) for (auto& i : c) cout << i << ' '; cout << '\n'
#define pp(c) for (auto& [f, s] : c) cout << f << " : " << s << '\n'
#define pr(c) for (auto& i:c) {for (auto& j:i) cout<<j<<' '; cout<<'\n';}
#define pn(c, n) for (int i = 0; i < n; ++i) cout<<c[i]<<' '; cout<<'\n'
#define pc(t) cout << "Case " << t << ":" << '\n'
const int M = 1e9 + 7, N = 120 + 5;
using namespace std;
int ar[N], pre[N], n;

void Accepted(int t) {
    cin >> n;
    for (int i = 0; i < n; ++i) { cin >> ar[i]; pre[i+1]=pre[i]+ar[i]; }
    multiset<int> st;
    pc(t);
    for(int i=0;i<n;++i){
        st.insert(ar[i]);
        if(pre[i+1]%3) cout<<0<<'\n';
        else{
            bool ck=0;
            multiset<int> st2=st;
            for(int j=0;j<2;++j){
                int tmp=pre[i+1]/3;
                while(tmp){
                    // if(i==4){pe(st2); ck(tmp);}
                    auto it=st2.lower_bound(tmp);
                    if(it==st2.begin() and *it!=tmp) {ck=1; cout<<0<<'\n'; break;}
                    else {
                        if(it==st2.end() or *it!=tmp) --it;
                        tmp-=*it;
                        st2.erase(it);
                    }
                }
                if(ck) break;
            }
            if(!ck) cout<<1<<'\n';
        }
    }
    // cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 0, tc = 1;
    cin >> tc;
    while(t < tc) Accepted(++t);
    return 0;
}