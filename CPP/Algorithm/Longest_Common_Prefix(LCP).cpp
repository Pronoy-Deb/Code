// Complexity: O(n * log(n))
// Note: Uses Kasai Algorithm to calculate the LCP array of a string.

long long suf[N], lcp[N], n; string s;
void pre() {
	map<string, int> mp; string sub;
	for (int i = n - 1; i >= 0; --i) {
		sub = s[i] + sub; mp[sub] = i;
	}
	int l = -1; for (auto &e : mp) suf[++l] = e.second;
	int rnk[n]{}, k = 0; for (int i = 0; i < n; ++i) rnk[suf[i]] = i;
	for (int i = 0; i < n; ++i) {
		if (rnk[i] == n - 1) {
			k = 0; continue;
		}
		int j = suf[rnk[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
		lcp[rnk[i]] = k; if (k) --k;
    }
}