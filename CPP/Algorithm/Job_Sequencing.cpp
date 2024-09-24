// Complexity: O(n * log(n))

pair<long long, long long> ar[N]; long long n;
auto js() {
	sort(ar, ar + n); long long c = 0, sum = 0;
	multiset<long long, greater<>> st;
	for (int i = n - 1; i >= 0; --i) {
		long long slot = ar[i].first - (i ? ar[i - 1].first : 0);
		st.insert(ar[i].second);
		while (slot-- && !st.empty()) {
			++c; sum += *st.begin();
			st.erase(st.begin());
		}
	}
	return make_pair(c, sum);
}

// Operation:
	cin >> n;
	for (i = 0; i < n; ++i) cin >> ar[i].first >> ar[i].second;
	auto ans = js();
	cout << ans.first << ' ' << ans.second << '\n';