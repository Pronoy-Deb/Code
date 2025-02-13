#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;

struct bit {
    int n; vector<int64_t> tre;
    bit(int _n) : n(_n + 5), tre(n) {}
    void add(int in, int64_t val) {
        for (++in; in <= n; in += in & -in) tre[in] += val;
    }
    void add(int l, int r, int64_t val) { add(l, val); add(++r, -val); }
    int64_t get(int in) {
        int64_t tot = 0;
        for (++in; in > 0; in -= in & -in) tot += tre[in];
        return tot;
    }
    int64_t get(int l, int r) { return get(r) - get(--l); }
} bt(0);

struct nd { int t, x, y, i, sgn, v; };
vector<nd> Q; vector<int> ans;
void cdq(int l, int r) {
    if (l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m); cdq(m, r);
  vector<nd> tmp;
  vector<pair<int, int> > his;
  int a = l, b = m;
  while(a < m || b < r) {
    if(b == r || (a < m && Q[a].x <= Q[b].x)) {
      bt.add(Q[a].y, Q[a].v);
      his.push_back({Q[a].y, Q[a].v});
      tmp.push_back(Q[a++]);
    }
    else {
      ans[Q[b].i] += Q[b].sgn * bt.get(Q[b].y);
      tmp.push_back(Q[b++]);
    }
  }
  for(auto [x, v] : his) bt.add(x, -v);
  for(int i = l ; i < r ; ++i) Q[i] = tmp[i - l];
  vector<nd> ().swap(tmp);
  vector<pair<int, int> > ().swap(his);
}

void init() {
  int n, m; cin >> n >> m;
  bt = bit(n);
  vector<int> a(n + 1), b(n + 1), pos(n + 1);
  for(int i = 1 ; i <= n ; ++i) cin >> a[i], pos[a[i]] = i;
  for(int i = 1 ; i <= n ; ++i) cin >> b[i];
  Q.clear();
  ans.push_back(0);
  for(int i = 1 ; i <= n ; ++i) Q.push_back({(int)Q.size(), pos[b[i]], i, 0, 0, 1});
  while(m--) {
    int op; cin >> op;
    if(op == 1) {
      int la, ra, lb, rb; cin >> la >> ra >> lb >> rb;
      Q.push_back({(int)Q.size(), ra, rb, (int)ans.size(), 1, 0});
      Q.push_back({(int)Q.size(), la - 1, rb, (int)ans.size(), -1, 0});
      Q.push_back({(int)Q.size(), ra, lb - 1, (int)ans.size(), -1, 0});
      Q.push_back({(int)Q.size(), la - 1, lb - 1, (int)ans.size(), 1, 0});
      ans.push_back(0);
    }
    else {
      int x, y; cin >> x >> y;
      Q.push_back({(int)Q.size(), pos[b[x]], x, 0, 0, -1});
      Q.push_back({(int)Q.size(), pos[b[y]], y, 0, 0, -1});
      swap(b[x], b[y]);
      Q.push_back({(int)Q.size(), pos[b[x]], x, 0, 0, 1});
      Q.push_back({(int)Q.size(), pos[b[y]], y, 0, 0, 1});
    }
  }
}
void solve() {
  cdq(0, (int)Q.size());
  for(int i = 1 ; i < (int)ans.size() ; ++i) cout << ans[i] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}