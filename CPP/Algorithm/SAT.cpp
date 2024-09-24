// 2 SAT:
// Complexity: O(n + m)

long long n;
vector<vector<long long>> adj, adj_t;
vector<bool> used, assignment;
vector<long long> order, comp;

void dfs1(long long v) {
    used[v] = true;
    for (auto &u : adj[v]) {
        if (!used[u]) dfs1(u);
    }
    order.push_back(v);
}
void dfs2(long long v, long long cl) {
    comp[v] = cl;
    for (auto &u : adj_t[v]) {
        if (comp[u] == -1) dfs2(u, cl);
    }
}
bool sat() {
    order.clear(); used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) dfs1(i);
    }
    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        long long v = order[n - i - 1];
        if (comp[v] == -1) dfs2(v, j++);
    }
    assignment.assign(n >> 1, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1]) return false;
        assignment[i >> 1] = comp[i] > comp[i + 1];
    }
    return true;
}
void add(long long a, bool na, long long b, bool nb) {
    a = (a << 1) ^ na; b = (b << 1) ^ nb;
    long long neg_a = a ^ 1, neg_b = b ^ 1;
    adj[neg_a].push_back(b); adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a); adj_t[a].push_back(neg_b);
}

// OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

/*
zero Indexed
we have vars variables
F=(x_0 XXX y_0) and (x_1 XXX y_1) and ... (x_{vars-1} XXX y_{vars-1})
here {x_i,y_i} are variables
and XXX belongs to {OR,XOR}
is there any assignment of variables such that F=true
*/
struct twosat {
  int n;  // total size combining +, -. must be even.
  vector< vector<int> > g, gt;
  vector<bool> vis, res;
  vector<int> comp;
  stack<int> ts;
  twosat(int vars = 0) {
    n = vars << 1;
    g.resize(n);
    gt.resize(n);
  }

  //zero indexed, be careful
  //if you want to force variable a to be true in OR or XOR combination
  //add addOR (a,1,a,1);
  //if you want to force variable a to be false in OR or XOR combination
  //add addOR (a,0,a,0);

  //(x_a or (not x_b))-> af=1,bf=0
  void addOR(int a, bool af, int b, bool bf) {
    a += a + (af ^ 1);
    b += b + (bf ^ 1);
    g[a ^ 1].push_back(b);  // !a => b
    g[b ^ 1].push_back(a);  // !b => a
    gt[b].push_back(a ^ 1);
    gt[a].push_back(b ^ 1);
  }
  //(!x_a xor !x_b)-> af=0, bf=0
  void addXOR(int a, bool af, int b, bool bf) {
    addOR(a, af, b, bf);
    addOR(a, !af, b, !bf);
  }
  void _add(int a,bool af,int b,bool bf) {
    a += a + (af ^ 1);
    b += b + (bf ^ 1);
    g[a].push_back(b);
    gt[b].push_back(a);
  }
  //add this type of condition->
  //add(a,af,b,bf) means if a is af then b must need to be bf
  void add(int a,bool af,int b,bool bf) {
    _add(a, af, b, bf);
    _add(b, !bf, a, !af);
  }
  void dfs1(int u) {
    vis[u] = true;
    for(int v : g[u]) if(!vis[v]) dfs1(v);
    ts.push(u);
  }
  void dfs2(int u, int c) {
    comp[u] = c;
    for(int v : gt[u]) if(comp[v] == -1) dfs2(v, c);
  }
  bool ok() {
    vis.resize(n, false);
    for(int i = 0; i < n; ++i) if(!vis[i]) dfs1(i);
    int scc = 0;
    comp.resize(n, -1);
    while(!ts.empty()) {
      int u = ts.top();
      ts.pop();
      if(comp[u] == -1) dfs2(u, scc++);
    }
    res.resize(n / 2);
    for(int i = 0; i < n; i += 2) {
      if(comp[i] == comp[i + 1]) return false;
      res[i / 2] = (comp[i] > comp[i + 1]);
    }
    return true;
  }
};

int main() {
  int n, m; cin >> n >> m;
  twosat ts(n);
  for(int i = 0; i < m; i++){
    int u, v, k; cin >> u >> v >> k;
    --u; --v;
    if(k) ts.add(u, 0, v, 0), ts.add(u, 1, v, 1), ts.add(v, 0, u, 0), ts.add(v, 1, u, 1);
    else ts.add(u, 0, v, 1), ts.add(u, 1, v, 0), ts.add(v, 0, u, 1), ts.add(v, 1, u, 0);
  }
  int k = ts.ok();
  if(!k) cout<<"Impossible\n";
  else {
    vector<int> v;
    for(int i = 0; i < n; i++) if(ts.res[i]) v.push_back(i);
    cout << (int)v.size() << '\n';
    for(auto x: v) cout << x + 1 << ' ';
    cout << '\n';
  }
  return 0;
}

// 3 SAT:

/*
We are given a CNF, e.g. phi(x) = (x_1 or ~x_2) and (x_3 or ~x_4 or ~x_5) and ... .
SAT finds an assignment x for phi(x) = true.
Davis-Putnum-Logemann-Loveland Algorithm
Complexity: O(2^n) in worst case.
This implementation is practical for n <= 1000 or more. lmao.
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// positive literal  x in [0,n),
// negative literal ~x in [-n,0)
// 0 indexed
struct SAT_GOD {
  int n;
  vector<int> occ, pos, neg;
  vector<vector<int>> g, lit;
  SAT_GOD(int n) : n(n), g(2*n), occ(2*n) { }
  void add_clause(const vector<int> &c) {
    for(auto u: c) {
      g[u+n].push_back(lit.size());
      occ[u+n] += 1;
    }
    lit.push_back(c);
  }
  //(!u | v | !w) -> (u, 0, v, 1, w, 0)
  void add(int u, int af, int v = 1e9, int bf = 0, int w = 1e9, int cf = 0) {
    vector<int> a;
    if(!af) u = ~u;
    a.push_back(u);
    if(v != 1e9) {
      if(!bf) v = ~v;
      a.push_back(v);
    }
    if(w != 1e9) {
      if(!cf) w = ~w;
      a.push_back(w);
    }
    add_clause(a);
  }
  vector<bool> x;
  vector<vector<int>> decision_stack;
  vector<int> unit_stack, pure_stack;
  void push(int u) {
    x[u + n] = 1;
    decision_stack.back().push_back(u);
    for (auto i: g[u + n]) if (pos[i]++ == 0) {
        for (auto u: lit[i]) --occ[u+n];
      }
    for (auto i: g[~u + n]) {
      ++neg[i];
      if (pos[i] == 0) unit_stack.push_back(i);
    }
  }
  void pop() {
    int u = decision_stack.back().back();
    decision_stack.back().pop_back();
    x[u + n] = 0;
    for (auto i: g[u + n]) if (--pos[i] == 0) {
        for (auto u: lit[i]) ++occ[u + n];
      }
    for (auto i: g[~u+n]) --neg[i];
  }
  bool reduction() {
    while(!unit_stack.empty() || !pure_stack.empty()) {
      if(!pure_stack.empty()) {  // pure literal elimination
        int u = pure_stack.back();
        pure_stack.pop_back();
        if (occ[u + n] == 1 && occ[~u + n] == 0) push(u);
      } else {                   // unit propagation
        int i = unit_stack.back();
        unit_stack.pop_back();
        if(pos[i] > 0) continue;
        if(neg[i]     == lit[i].size()) return false;
        if(neg[i] + 1 == lit[i].size()) {
          int w = n;
          for (int u: lit[i]) if (!x[u + n] && !x[~u + n]) w = u;
          if (x[~w + n]) return false;
          push(w);
        }
      }
    }
    return true;
  }
  bool ok() {
    x.assign(2*n,0);
    pos = neg = vector<int>(lit.size());
    decision_stack.assign(1, {});
    while(1) {
      if(reduction()) {
        int s = 0;
        for(int u = 0; u < n; ++u) if(occ[s + n] + occ[~s + n] < occ[u + n] + occ[~u + n]) s = u;
        if(occ[s + n] + occ[~s + n] == 0) return true;
        decision_stack.push_back({});
        push(s);
      } else {
        int s = decision_stack.back()[0];
        while(!decision_stack.back().empty()) pop();
        decision_stack.pop_back();
        if (decision_stack.empty()) return false;
        push(~s);
      }
    }
  }
};

int32_t main() {
  int n = 9;
  SAT_GOD t(n);
  t.add(0, 0, 1, 1);
  t.add(1, 0);
  t.add(1, 0, 3, 1, 5, 1);
  cout << t.ok() << endl;
}