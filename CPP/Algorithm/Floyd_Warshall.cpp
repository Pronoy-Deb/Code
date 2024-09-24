// Complexity: O(n^3)
// Use: Used to determine the shortest distance of all connected nodes

long long dis[N][N];
void pre(int vr) {
    for (int k = 1; k <= vr; ++k) {
        for (int i = 1; i <= vr; ++i) {
            for (int j = 1; j <= vr; ++j) {
                dis[i][j] = (i == j ? 0 : min(dis[i][j], dis[i][k] + dis[k][j]));
            }
        }
    }
}

// Operation:
    int vr, eg; cin >> vr >> eg;
    fill(&dis[0][0], &dis[0][0] + (N * N), LLONG_MAX);
    for(i = 0; i < eg; ++i) {
        long long v1, v2, wt; cin >> v1 >> v2 >> wt;
        dis[v1][v2] = wt;
        // g[v2].emplace_back(v1, wt); // In case of undirected graph
    }
    pre(vr);
    for(i = 1; i <= vr; ++i) {
        for(j = 1; j <= vr; ++j)
            cout << (dis[i][j] == INT_MAX ? -1 : dis[i][j]) << ' '; cout << '\n';
    }

// OR,

#include<bits/stdc++.h>
using namespace std;

const int N = 105;
int d[N][N];
int main() {
  int n = 10;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) {
        d[i][j] = 1e9;
      }
    }
  }
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  return 0;
}