// Complexity: O(|str| + |pat|)
// Application: Used to find all occurrences of a pattern in a text in linear time

vector<int> ind;
auto z(auto &str, auto &pat) {
    int pl = pat.size(); pat += '$' + str;
	int tl = pat.size(), Z[tl], l = 0, r = 0;
	for (int i = 1; i < tl; ++i) {
		if (i > r) {
			l = r = i;
			while (r < tl && pat[r - l] == pat[r]) ++r;
			Z[i] = r - l; --r;
		}
		else {
			if (Z[i - l] < r - i + 1) Z[i] = Z[i - l];
			else {
				l = i;
				while (r < tl && pat[r - l] == pat[r]) ++r;
				Z[i] = r - l; --r;
			}
		}
	}
    // return count(Z, Z+tl, pl);  // To determine the number of occurrences
	for (int i = 0; i < tl; ++i) {
		if (Z[i] == pl) ind.emplace_back(i - pl - 1);
	}
}

// Problem: lightoj.com/problem/substring-frequency

// OR,

#include<bits/stdc++.h>
using namespace std;

// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].
// The first entry of Z array is meaning less as complete string is always prefix of itself.
// Here Z[0]=0.
vector<int> z_function(string s) {
  int n = (int) s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}
int32_t main() {
  string s;
  cin >> s;
  vector<int>  ans = z_function(s);
  for(auto x : ans) cout << x << ' ';
  return 0;
}