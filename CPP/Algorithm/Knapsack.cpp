// Complexity: O(n * w)

long long wt[N], val[N], dp[N][N];
long long rec(int in, int w) {
    if (!w || in < 0) return 0;
	auto &ans = dp[in][w]; if (~ans) return dp[in][w];
	ans = rec(in - 1, w);
    if (w >= wt[in]) ans = max(ans, rec(in - 1, w - wt[in]) + val[in]);
    return ans;
}
void reset(int in, int w) {
	if (!w || in < 0) return;
	dp[in][w] = -1; reset(in - 1, w);
	if (w >= wt[in]) reset(in - 1, w - wt[in]);
}

// Operation:
	long long w; cin >> n >> w;
	for (i = 0; i < n; ++i) {
		cin >> wt[i] >> val[i];
	}
	memset(dp, -1, sizeof(dp));
	cout << rec(n - 1, w);

// 0-1 Knapsack: O(n * wt)
// wt = Total weight, p = profit, w = weight.
https://cses.fi/problemset/task/1158/

long long n, wt, dp[N], w[N], p[N];
long long knap() {
    for(int i = 0; i < n; ++i) {
        for(int j = wt; j >= w[i]; --j) {
            dp[j] = max(dp[j], p[i] + dp[j - w[i]]);
        }
    }
    return dp[wt];
}

// Operation:
    cin >> n >> wt;
    for (i = 0; i < n; ++i) cin >> w[i];
    for (i = 0; i < n; ++i) cin >> p[i];
    cout << knap();

// Bounded Knapsack:
#include <bits/stdc++.h>
using namespace std;

// ps-profits
// ws-weights
// ms-maximum limit of each element
// W-maximum weight
// O(n*W)
int boundedKnapsack(vector<int> ps, vector<int> ws, vector<int> ms, int W) {
    int n = ps.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));
    for (int i = 0; i < n; ++i) {
        for (int s = 0; s < ws[i]; ++s) {
            int alpha = 0;
            queue<int> que;
            deque<int> peek;
            for (int w = s; w <= W; w += ws[i]) {
                alpha += ps[i];
                int a = dp[i][w] - alpha;
                que.push(a);
                while (!peek.empty() && peek.back() < a) peek.pop_back();
                peek.push_back(a);
                while (que.size() > ms[i] + 1) {
                    if (que.front() == peek.front()) peek.pop_front();
                    que.pop();
                }
                dp[i + 1][w] = peek.front() + alpha;
            }
        }
    }
    int ans = 0;
    for (int w = 0; w <= W; ++w)
        ans = max(ans, dp[n][w]);
    return ans;
}
int32_t main() {
    int i, j, k, n, m;
    n = 10;
    int W = 100;
    vector<int> ps(n), ws(n), ms(n);
    for (int i = 0; i < n; ++i) {
        ps[i] = rand() % n + 1;
        ws[i] = rand() % n + 1;
        ms[i] = rand() % n + 1;
    }
    cout << boundedKnapsack(ps, ws, ms, W) << endl;
    return 0;
}
