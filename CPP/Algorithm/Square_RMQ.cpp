// Complexity: O()
// RMQ for - Square Queries
// K = side of the square is 2^k

const int64_t N = 505, K = 10;
int64_t st[N][N][K], n;
int64_t bit(int64_t n) { return 1ll << n; }
void pre() {
    for (int k = 1; bit(k) <= n; ++k) {
        for (int i = 1; i + bit(k) - 1 <= n; ++i) {
            for (int j = 1; j + bit(k) - 1 <= n; ++j) {
                int x = i + bit(k - 1), y = j + bit(k - 1);
                st[i][j][k] = max(st[i][j][k - 1], st[i][y][k - 1]);
                st[i][j][k] = max(st[i][j][k], max(st[x][j][k - 1], st[x][y][k - 1]));
            }
        }
    }
}

// upper left corner, size of a side
int64_t get(int i, int j, int d) {
    int k = log2(d), x = i + d - 1, y = j + d - 1;
    int64_t m1 = max(st[i][j][k], st[i][y - bit(k) + 1][k]);
    int64_t m2 = max(st[x - bit(k) + 1][j][k], st[x - bit(k) + 1][y - bit(k) + 1][k]);
    return max(m1, m2);
}

// Operation:
    cin >> n >> q;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) cin >> st[i][j][0];
    }
    pre();
    while (q--) {
        int x, y, l; cin >> x >> y >> l;
        cout << get(x, y, l) << "\n";
    }

// Problem: https://lightoj.com/problem/square-queries