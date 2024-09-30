const int N = 5e2 + 5, L = 10;
long long tab[N][N][L][L], ar[N][N], n, m;
void make() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) tab[i][j][0][0] = ar[i][j];
	}
    int lgn = log2(n), lgm = log2(m);
    for (int k = 1; k <= lgn; ++k) {
		for (int i = 0; i + (1 << k) - 1 < n; ++i) {
			for (int j = 0; j + (1 << k) - 1 < m; ++j)
				tab[i][j][k][0] = min(tab[i][j][k - 1][0], tab[i + (1 << (k - 1))][j][k - 1][0]);
		}
	}
	for (int k = 1; k <= lgm; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j + (1 << k) - 1 < m; ++j) {
                tab[i][j][0][k] = min(tab[i][j][0][k - 1], tab[i][j + (1 << (k - 1))][0][k - 1]);
			}
		}
	}
	for (int k = 1; k <= lgn; ++k) {
		for (int l = 1; l <= lgm; ++l) {
			for (int i = 0; i + (1 << k) - 1 < n; ++i) {
				for (int j = 0; j + (1 << l) - 1 < m; ++j)
                    tab[i][j][k][l] = min({tab[i][j][k - 1][l - 1], tab[i + (1 << (k - 1))][j][k - 1][l - 1], tab[i][j + (1 << (l - 1))][k - 1][l - 1], tab[i + (1 << (k - 1))][j + (1 << (l - 1))][k - 1][l - 1]});
			}
		}
	}
}
long long get(int x1, int y1, int x2, int y2) {
	int k = log2(x2 - x1 + 1), l = log2(y2 - y1 + 1);
	return max({tab[x1][y1][k][l], tab[x2 - (1 << k) + 1][y1][k][l], tab[x1][y2 - (1 << l) + 1][k][l], tab[x2 - (1 << k) + 1][y2 - (1 << l) + 1][k][l]});
}