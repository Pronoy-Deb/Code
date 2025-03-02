// Suffix Automaton:

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// len -> largest string length of the corresponding endpos-equivalent class
// link -> longest suffix that is another endpos-equivalent class.
// firstpos -> 1 indexed end position of the first occurrence of the largest string of that node
// minlen(v) -> smallest string of node v = len(link(v)) + 1
// terminal nodes -> store the suffixes
struct SuffixAutomaton {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    vector<int> terminal;
    vector<int64_t> dp;
    vector<vector<int>> g;
    SuffixAutomaton() {}
    SuffixAutomaton(int n) {
        t.resize(2 * n); terminal.resize(2 * n, 0);
        dp.resize(2 * n, -1); sz = 1; last = 0;
        g.resize(2 * n);
        t[0].len = 0; t[0].link = -1; t[0].firstpos = 0;
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    void build_tree() {
        for (int i = 1; i < sz; i++) g[t[i].link].push_back(i);
    }
    void build(string &s) {
        for (auto x: s) {
            extend(x);
            terminal[last] = 1;
        }
        build_tree();
    }
    int64_t cnt(int i) { //number of times i-th node occurs in the string
        if (dp[i] != -1) return dp[i];
        int64_t ret = terminal[i];
        for (auto &x: g[i]) ret += cnt(x);
        return dp[i] = ret;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        SuffixAutomaton sa(n);
        sa.build(s);
        int64_t ans = 0; //number of unique substrings
        for (int i = 1; i < sa.sz; i++) ans += sa.t[i].len - sa.t[sa.t[i].link].len;
        cout << ans << '\n';
    }
    return 0;
}


// Suffix Automaton Distinct Substring Queries in Range:

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

struct ST {
  #define lc (n << 1)
  #define rc ((n << 1) | 1)
  int64_t t[4 * N], lazy[4 * N];
  ST() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) {
    if (lazy[n] == 0) return;
    t[n] = t[n] + lazy[n] * (e - b + 1);
    if (b != e) {
      lazy[lc] = lazy[lc] + lazy[n];
      lazy[rc] = lazy[rc] + lazy[n];
    }
    lazy[n] = 0;
  }
  inline int64_t combine(int64_t a,int64_t b) {
    return a + b;
  }
  inline void pull(int n) {
    t[n] = t[lc] + t[rc];
  }
  void upd(int n, int b, int e, int i, int j, int v) {
    push(n, b, e);
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      lazy[n] = v; //set lazy
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  int64_t query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j) return 0; //return null
    if (i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
}st;

struct node {
  int len, link, firstpos;
  map<char, int> nxt;
};
vector<node> t;
struct SuffixAutomaton {
  int sz, last;
  vector<int> terminal;
  vector<int> dp;
  vector<vector<int>> g;
  SuffixAutomaton() {}
  SuffixAutomaton(int n) {
    t.clear(); t.resize(2 * n);
    terminal.resize(2 * n, 0);
    dp.resize(2 * n, -1); sz = 1; last = 0;
    g.resize(2 * n);
    t[0].len = 0; t[0].link = -1; t[0].firstpos = 0;
  }
  void extend(char c) {
    int p = last;
    int cur = sz++;
    t[cur].len = t[last].len + 1;
    t[cur].firstpos = t[cur].len;
    p = last;
    while (p != -1 && !t[p].nxt.count(c)) {
      t[p].nxt[c] = cur;
      p = t[p].link;
    }
    if (p == -1) t[cur].link = 0;
    else {
      int q = t[p].nxt[c];
      if (t[p].len + 1 == t[q].len) t[cur].link = q;
      else {
        int clone = sz++;
        t[clone] = t[q];
        t[clone].len = t[p].len + 1;
        while (p != -1 && t[p].nxt[c] == q) {
          t[p].nxt[c] = clone;
          p = t[p].link;
        }
        t[q].link = t[cur].link = clone;
      }
    }
    last = cur;
  }
};

pair<int, int> modifies[N * 2];
int cnt;
namespace lct {
  int par[N * 2], lazy[N * 2], last[N * 2], c[N * 2][2];
  void mark(int x, int v) {
    lazy[x] = last[x] = v;
  }
  void push(int x) {
    if (lazy[x]) {
      if (c[x][0]) {
        mark(c[x][0], lazy[x]);
      }
      if (c[x][1]) {
        mark(c[x][1], lazy[x]);
      }
      lazy[x] = 0;
    }
  }
  bool is_root(int x) {
    return c[par[x]][0] != x && c[par[x]][1] != x;
  }
  void rotate(int x) {
    int y = par[x], z = par[y], k = c[y][1] == x;
    if (!is_root(y)) {
      c[z][c[z][1] == y] = x;
    }
    par[c[y][k] = c[x][!k]] = y;
    par[par[c[x][!k] = y] = x] = z;
  }
  void splay(int x) {
    static int st[N];
    int top = 0;
    st[++top] = x;
    for (int i = x; !is_root(i); i = par[i]) {
      st[++top] = par[i];
    }
    while (top) {
      push(st[top--]);
    }
    while (!is_root(x)) {
      int y = par[x], z = par[y];
      if (!is_root(y)) {
        rotate((c[y][1] == x) == (c[z][1] == y) ? y : x);
      }
      rotate(x);
    }
  }
  void access(int x, int v) {
    int z = 0;
    cnt = 0;
    while (x) {
      splay(x);
      modifies[++cnt] = make_pair(t[x - 1].len, last[x]);
      c[x][1] = z;
      mark(x, v);
      z = x;
      x = par[x];
    }
  }
}

int pos[N];
vector<pair<int, int>> Q[N];
int64_t ans[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; cin >> n >> q;
  string s; cin >> s;
  SuffixAutomaton sa(n);
  for (int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    ++l; ++r;
    Q[r].push_back({l, i});
  }
  s = "." + s;
  pos[0] = 1;
  for (int i = 1; i <= n; ++i) {
    sa.extend(s[i]);
    pos[i] = sa.last + 1;
  }
  for (int i = 1; i <= sa.sz; ++i) {
    lct::par[i] = t[i - 1].link + 1;
  }
  for (int i = 1; i <= n; ++i) {
    st.upd(1, 1, n, 1, i, 1);
    lct::access(pos[i], i);
    int last = 0;
    for (int j = cnt; j > 1; --j) {
      pair<int, int> p = modifies[j];
      if (p.first) {
        if (p.second) {
          st.upd(1, 1, n, p.second - p.first + 1, p.second - last, -1);
        }
        last = p.first;
      }
    }
    // st.query(l, l) = number of distinct substrings which lastly occured in starting position l for prefix [1, i]
    for (auto [l, id]: Q[i]) {
      ans[id] = st.query(1, 1, n, l, i);
    }
  }
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
// https://www.hackerrank.com/challenges/how-many-substrings/problem
// https://codeforces.com/gym/102129/problem/I