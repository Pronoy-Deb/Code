{
	// Place your snippets for cpp here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	"Print to console": {
		"prefix": "te",
		"body": [
			// 		"console.log('$1');",
			// 		"$2"
			"#include <bits/stdc++.h>",
			"using namespace std;",
			"#define ll long long",
			"#define pe(c) for (auto &e : c) cout << e << ' '; cout << '\\n'"
			"#define ps(b) cout << (b ? \"YES\" : \"NO\") << '\\n'",
			"#define pc cout << \"Case \" << tc << \": \"",
			"#ifdef LOCAL",
			"#include \"def.h\"",
			"#else"
			"#define ck(...) ",
			"#endif",
			"const ll M = 1e9 + 7, N = 2e5 + 5;",
			"",
			"void test(int tc) {",
			"\tll a = 0, b = 0, c = 0, d = 0, i = 0, j = 0, k = 0, m = 0, n = 0, q = 0;",
			"\tcin >> n;",
			"\tvector<ll> ar(n); for (i = 0; i < n; ++i) { cin >> ar[i]; }",
			"\t$0",
			"\tcout << '\\n';",
			"}",
			"",
			"signed main() {",
			"\tcin.tie(0)->sync_with_stdio(0); cin.exceptions(cin.failbit | cin.badbit);",
			"\tint tc = 0, t = 1;",
			"\tcin >> t;",
			"\twhile (tc < t) test(++tc);",
			"\treturn 0;",
			"}",
		],
		"description": "Log output to console"
	}
}