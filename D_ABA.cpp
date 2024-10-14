#include <bits/stdc++.h>
const long long N = 2e5 + 5;
using namespace std;

long long l[26][N], r[26][N], n;
void pre(string &s) {
	l[s[0] - 'a'][0] = 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 26; ++j) l[j][i] += l[j][i - 1];
		++l[s[i] - 'a'][i];
	}
	r[s[n - 1] - 'a'][n - 1] = 1;
	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j < 26; ++j) r[j][i] += r[j][i + 1];
		++r[s[i] - 'a'][i];
	}
}
long long psk(int k) {
	long long ans = 0;
	if (k == 1) {
		for (int i = 0; i < 26; ++i) ans += l[i][n - 1];
		return ans;
	}
	if (k == 2) {
		for (int i = 0; i < 26; ++i) ans += ((l[i][n - 1] * (l[i][n - 1] - 1)) >> 1);
		return ans;
	}
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 0; j < 26; ++j) ans += l[j][i - 1] * r[j][i + 1];
	}
	return ans;
}
int main() {
    cin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);
    string s; cin >> s;
	n = s.size();
	pre(s);
	cout << psk(3) << '\n';
	return 0;
}
