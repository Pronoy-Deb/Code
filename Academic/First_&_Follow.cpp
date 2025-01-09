#include <bits/stdc++.h>
using namespace std;
const int N = 26;

int main() {
    cout << "Enter the number of production rules: ";
    int t; cin >> t; string pro[t];
    set<char> first[N], follow[N];
    vector<int> con[N], con2[N];
    cout << "Enter the production rules: ";
    for (int i = 0; i < t; ++i) {
        string s; cin >> s; pro[i] = s;
        int n = s.size();
        for (int j = 0; j < n - 1; ++j) {
            if (islower(s[j]) and isupper(s[j + 1])) first[s[0] - 'A'].insert(s[j]);
            if (islower(s[j + 1]) and isalpha(s[j])) follow[s[0] - 'A'].insert(s[j + 1]);
            if (isupper(s[j]) and s[j + 1] == '|') con[s[0] - 'A'].push_back(s[j] - 'A');
        }
        if (s[n - 1] == '@' and s[n - 2] == '|')
            first[s[0] - 'A'].insert(s[n - 1]);
        else if (isupper(s[n - 1]))
            con2[s[0] - 'A'].push_back(s[n - 1] - 'A');
    }
    for (int i = 0; i < N; ++i) {
        for (auto ele : con[i])
            for (auto e : first[ele]) first[i].insert(e);
        for (auto ele : con2[i])
            for (auto e : follow[ele]) follow[i].insert(e);
    }
    cout << "Productions\tFirst\tFollow\n";
    for (int i = 0; i < t; ++i) {
        cout << pro[i] << '\t';
        if (!first[pro[i][0] - 'A'].empty()) {
            for (auto e : first[pro[i][0] - 'A']) cout << e << ' ';
            cout << '\t';
        }
        cout << '@' << ' ';
        if (!follow[pro[i][0] - 'A'].empty()) {
            for (auto e : follow[pro[i][0] - 'A']) cout << e << ' ';
            cout << '\n';
        }
    }
    return 0;
}