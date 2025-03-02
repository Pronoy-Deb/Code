// Complexity: O(n * log(n))

pair<int64_t, int64_t> aa[N]; int64_t n;
auto js() {
	sort(ar, ar + n); int64_t c = 0, sum = 0;
	multiset<int64_t, greater<>> st;
	for (int i = n - 1; i >= 0; --i) {
		int64_t slot = aa[i].first - (i ? aa[i - 1].first : 0);
		st.insert(aa[i].second);
		while (slot-- && !st.empty()) {
			++c; sum += *st.begin();
			st.erase(st.begin());
		}
	}
	return make_pair(c, sum);
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> aa[i].first >> aa[i].second;
	auto ans = js();
	cout << ans.first << ' ' << ans.second << '\n';