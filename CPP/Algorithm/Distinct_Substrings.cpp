// Complexity: O(n*log(n))
// Use: Used to determine the number of unique substrings in a string using suffix array and lcp array of kasai algorithm.

string s; long long n;
struct suff { long long in, rnk[2]; };
auto cmp(struct suff a, struct suff b) { return (a.rnk[0] == b.rnk[0]) ? (a.rnk[1] < b.rnk[1]) : (a.rnk[0] < b.rnk[0]); }
auto dsub() {
	struct suff sfx[n];
	for (int i = 0; i < n; ++i) {
		sfx[i].in = i; sfx[i].rnk[0] = s[i] - 'a';
		sfx[i].rnk[1] = (i + 1 < n) ? (s[i + 1] - 'a') : -1;
	}
	sort(sfx, sfx + n, cmp); long long ind[n];
	for (long long k = 4; k < (n << 1); k <<= 1) {
		long long rnk = 0, prev = sfx[0].rnk[0];
		sfx[0].rnk[0] = rnk; ind[sfx[0].in] = 0;
		for (int i = 1; i < n; ++i) {
			if (sfx[i].rnk[0] == prev && sfx[i].rnk[1] == sfx[i - 1].rnk[1]) {
				prev = sfx[i].rnk[0]; sfx[i].rnk[0] = rnk;
			}
			else {
				prev = sfx[i].rnk[0]; sfx[i].rnk[0] = ++rnk;
			}
			ind[sfx[i].in] = i;
		}
		for (int i = 0; i < n; ++i) {
			long long nxt = sfx[i].in + (k >> 1);
			sfx[i].rnk[1] = (nxt < n) ? sfx[ind[nxt]].rnk[0] : -1;
		}
		sort(sfx, sfx + n, cmp);
	}
    long long suf[n], lcp[n], inv[n], k = 0;
    for (int i = 0; i < n; ++i) { suf[i] = sfx[i].in; inv[suf[i]] = i; }
	for (int i = 0; i < n; ++i) {
		if (inv[i] == n - 1) { k = 0; continue; }
		long long j = suf[inv[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
		lcp[inv[i]] = k; k -= (k > 0);
    }
    long long res = n - suf[0];
    for (int i = 1; i < n; ++i) res += (n - suf[i]) - lcp[i - 1];
	return res;
}