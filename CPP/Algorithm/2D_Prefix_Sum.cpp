// Complexity: O(n^2)
// -> For the same array:

int64_t aa[r + 1][c + 1];
void cal() {
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> aa[i][j];
            aa[i][j] += (aa[i - 1][j] + aa[i][j - 1] - aa[i - 1][j - 1]);
        }
    }
}
// To output the summation of a specific rectangular shaped range (x1,y1,x2,y2):
    cout << aa[x2][y2] - aa[x1 - 1][y2] - aa[x2][y1 - 1] + aa[x1 - 1][y1 - 1];

// -> For a different array:

int64_t aa[r + 1][c + 1], sum[r + 1][c + 1];
void cal() {
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> aa[i][j];
            sum[i][j] = aa[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
}
// To output the summation of a specific rectangular shaped range (x1,y1,x2,y2):
    cout << sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];