// Complexity: O(n*(log(log(n))))

pair<int64_t, int64_t> lh[N]; bitset<N> sv;
void pre() {
    lh[2].first = lh[2].second = 2;
    for (int i = 4; i < N; i += 2) {
        sv[i] = true; lh[i].first = lh[i].second = 2;
    }
    for (int i = 3; i < N; i += 2) {
        if (!sv[i]) {
            lh[i].first = lh[i].second = i;
            for (int j = (i << 1); j < N; j += i) {
                sv[j] = true;
                if (!lh[j].first) lh[j].first = i;
                lh[j].second = i;
            }
        }
    }
}