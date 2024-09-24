// Complexity: O(n^2)
// -> For the same array:

long long ar[r + 1][c + 1];
void cal() {
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> ar[i][j];
            ar[i][j] += (ar[i - 1][j] + ar[i][j - 1] - ar[i - 1][j - 1]);
        }
    }
}
// To output the summation of a specific rectangular shaped range (x1,y1,x2,y2):
    cout << ar[x2][y2] - ar[x1 - 1][y2] - ar[x2][y1 - 1] + ar[x1 - 1][y1 - 1];

// -> For a different array:

long long ar[r + 1][c + 1], sum[r + 1][c + 1];
void cal() {
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> ar[i][j];
            sum[i][j] = ar[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
}
// To output the summation of a specific rectangular shaped range (x1,y1,x2,y2):
    cout << sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];