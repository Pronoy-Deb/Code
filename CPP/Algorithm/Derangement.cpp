// Total Number of Derangements:
https://cses.fi/problemset/task/1717

int64_t dr[N];
void pre() {
    dr[0] = 1; dr[1] = 0;
    for (int i = 2; i < N; ++i) dr[i] = (i - 1) * (dr[i - 1] + dr[i - 2]) % M;
}