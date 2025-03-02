// Addition: O(max(n, m))

void sum(auto &s, auto &s1, auto &ans) {
    int sz = s.size() - 1, sz1 = s1.size() - 1, car = 0;
    for (int i = sz, j = sz1; i >= 0 || j >= 0; --i, --j) {
        int tmp = (i >= 0 ? (s[i] - 48) : 0) + (j >= 0 ? (s1[j] - 48) : 0) + car;
        if (tmp > 9) { car = tmp / 10; tmp %= 10; } else car = 0;
        ans += (tmp + 48);
    }
    if (car) ans += (car + 48); reverse(ans.begin(), ans.end());
}

// Subtraction: O(n + m)

void sub(auto &s, auto &s1, auto &ans) {
    int sz = s.size() - 1, sz1 = s1.size() - 1; bool ok = false;
    if ((sz < sz1) || (sz == sz1 && s < s1)) {
        ok = true; swap(s, s1); swap(sz, sz1);
    }
    bool car = false;
    for (int i = sz, j = sz1; i >= 0; --i, --j) {
        if (j >= 0) {
            if ((s[i] - car) < s1[j]) { ans += (s[i] + 10 - s1[j] - car + 48); car = true; }
            else { ans += (s[i] - s1[j] - car + 48); car = false; }
        }
        else {
            if (s[i] - car < 48) { ans += (s[i] + 10 - car); car = true; }
            else { ans += (s[i] - car); car = false; }
        }
    }
    while (ans.back() == '0' && ans.size() > 1) ans.pop_back();
    if (ok and ans.back() != '0') ans += '-';
    reverse(ans.begin(), ans.end());
}

// Multiplication: O(n * m), Note: Initially pro is empty!

void mul(auto &s, auto &s1, auto &pro) {
    if (s == "0" || s1 == "0") { pro += "0"; return; }
    int sz = s.size() - 1, sz1 = s1.size() - 1, car = 0;
    for (int i = 0; i <= sz + sz1 || car; ++i) {
        int tmp = min(i, sz);
        for (int j = max(0, i - sz1); j <= tmp; ++j)
            car += (s[sz - j] - 48) * (s1[sz1 - i + j] - 48);
        pro += (car % 10 + 48); car /= 10;
    }
    reverse(pro.begin(), pro.end());
}

// Division: O((n * m)!) // Results the Qoutient without rm
// Calling: string s = "32", ans; qnt(s, 3, ans); // ans = "10"

void qnt(auto &dnd, int dsr, auto &ans) {
	int in = 0, tmp = dnd[in] - 48, sz = dnd.size();
	while (tmp < dsr) tmp = tmp * 10 + (dnd[++in] - 48);
	while (sz > in) {
		ans += ((tmp / dsr) + 48);
		tmp = (tmp % dsr) * 10 + dnd[++in] - 48;
	}
    if (ans.empty()) ans += "0";
}

// Remainder: O(|num|)

int rem(string &num, int mod) {
    // string div;
    int rm = 0, sz = num.size();
    for (int i = 0; i < sz; ++i) {
        rm = (rm * 10) + (num[i] - '0');
        // if (rm >= mod) div += (rm / mod) + '0';
        // else if (!div.empty()) div += '0';
        rm %= mod;
    }
    return rm;
}

// Binary Exponentiation: O(|ans| * log(pow))
// Calling: string s = "2", ans = "1"; bex(s, 32, ans);

string mul(auto &s, auto &s1) {
    if (s == "0" || s1 == "0") return "0"; string pro;
    int sz = s.size() - 1, sz1 = s1.size() - 1, car = 0;
    for (int i = 0; i <= sz + sz1 || car; ++i) {
        int tmp = min(i, sz);
        for (int j = max(0, i - sz1); j <= tmp; ++j)
            car += (s[sz - j] - 48) * (s1[sz1 - i + j] - 48);
        pro += (car % 10 + 48); car /= 10;
    }
    reverse(pro.begin(), pro.end()); return pro;
}
void bex(auto &base, long long pow, auto &ans) {
    while (pow) {
        if (pow & 1) ans = mul(ans, base);
        base = mul(base, base); pow >>= 1;
    }
}