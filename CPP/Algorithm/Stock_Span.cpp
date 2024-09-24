// Complexity: O(n)
// Application: Used to determine the number of consecutive smaller elements of a number before it.
// Stack Approach:

long long ans[N], price[N], n;
void ss() {
	stack<long long> sk; sk.push(0); ans[0] = 1;
	for (int i = 1; i < n; ++i) {
		while (!sk.empty() && price[sk.top()] <= price[i]) sk.pop();
		ans[i] = (sk.empty()) ? (i + 1) : (i - sk.top());
		sk.push(i);
	}
}

// DP Approach:

long long ans[N], ar[N], n;
void ss() {
	ans[0] = 1;
	for (int i = 1; i < n; ++i) {
		int cnt = 1;
		while (i - cnt >= 0 && ar[i] >= ar[i - cnt]) cnt += ans[i - cnt];
		ans[i] = cnt;
	}
}