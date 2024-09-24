// Addition:
// Complexity: O(max(|s|, |s1|));

auto sum(auto &s, auto &s1) {
    int sz = s.size() - 1, sz1 = s1.size() - 1;
    string r; long long car = 0;
    for (int i = sz, j = sz1; i >= 0 || j >= 0; --i, --j) {
        long long tmp = (i >= 0 ? (s[i] - 48) : 0) + (j >= 0 ? (s1[j] - 48) : 0) + car;
        if (tmp > 9) { car = tmp / 10; tmp %= 10; } else car = 0;
        r += (tmp + 48);
    }
    if (car) r += (car + 48);
    reverse(r.begin(), r.end()); return r;
}

// Subtraction:
// Complexity: O(|s| + |s1|);

auto sub(auto &s, auto &s1) {
    int sz = s.size() - 1, sz1 = s1.size() - 1; bool ck = false;
    if ((sz < sz1) || (sz == sz1 && s < s1)) { ck = true; swap(s, s1); swap(sz, sz1); }
    string r; bool car = false;
    for (int i = sz, j = sz1; i >= 0; --i, --j) {
        if (j >= 0) {
            if ((s[i] - car) < s1[j]) { r += (s[i] + 10 - s1[j] - car + 48); car = true; }
            else { r += (s[i] - s1[j] - car + 48); car = false; }
        }
        else {
            if (s[i] - car < 48) { r += (s[i] + 10 - car); car = true; }
            else { r += (s[i] - car); car = false; }
        }
    }
    while (r.back() == '0' && r.size() > 1) r.pop_back();
    if (ck) r += '-';
    reverse(r.begin(), r.end()); return r;
}

// Multiplication:
// Complexity: O(|s| * |s1|)

auto mul(auto &s, auto &s1) {
    if (s == "0" || s1 == "0") return "0";
    int sz = s.size() - 1, sz1 = s1.size() - 1, car = 0; string pro;
    for (int i = 0; i <= sz + sz1 || car; ++i) {
        int tmp = min(i, sz);
        for (int j = max(0, i - sz1); j <= tmp; ++j)
            car += (s[sz - j] - 48) * (s1[sz1 - i + j] - 48);
        pro += (car % 10 + 48);
        car /= 10;
    }
    reverse(pro.begin(), pro.end()); return pro;
}

// Division:
// Complexity: O((n^2)!)

auto div(auto &num, auto div) {
	int idx = 0, tmp = num[idx] - 48, sz = num.size();
	while (tmp < div) tmp = tmp * 10 + (num[++idx] - 48);
	string ans;
	while (sz > idx) {
		ans += ((tmp / div) + 48);
		tmp = (tmp % div) * 10 + num[++idx] - 48;
	}
    return (ans.empty() ? "0" : ans);
}