#include<bits/stdc++.h>
using namespace std;

void And(auto &v) {
    int n = 4; map<pair<int, string>, vector<int> > mp;
    for (int i = 0; i < n; ++i) mp[{i, v[0]}].push_back(i);
    mp[{0, v[1]}].push_back(1); mp[{1, v[0]}].push_back(2);
    mp[{2, v[2]}].push_back(3);
    cout << "State\t" << v[0] << '\t' << v[1] << '\t' << v[2] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if (i == n - 1) cout << "*";
        cout << i << '\t';
        for (auto e : v) {
            if (mp.find({i, e}) != mp.end()) {
                for (auto ee : mp[{i, e}]) cout << ee << ' ';
                cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << endl;
    }
}

void Or(auto &v) {
    int n = 6; map<pair<int, string>, vector<int> > mp;
    for (int i = 0; i < n; ++i) mp[{i, v[0]}].push_back(i);
    mp[{0, v[0]}].push_back(1);
    mp[{0, v[0]}].push_back(2);
    mp[{1, v[1]}].push_back(3);
    mp[{2, v[2]}].push_back(4);
    mp[{3, v[0]}].push_back(5);
    mp[{4, v[0]}].push_back(5);
    cout << "State\t" << v[0] << '\t' << v[1] << '\t' << v[2] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if (i == n - 1) cout << "*";
        cout << i << '\t';
        for (auto e : v) {
            if (mp.find({i, e}) != mp.end()) {
                for (auto ee : mp[{i, e}]) cout << ee << ' ';
                cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << endl;
    }
}

void Star(auto &v) {
    int n = 4;
    map<pair<int, string>, vector<int> > mp;
    for (int i = 0; i < n; ++i) mp[{i, v[0]}].push_back(i);
    mp[{0, v[0]}].push_back(1);
    mp[{0, v[0]}].push_back(3);
    mp[{1, v[1]}].push_back(2);
    mp[{2, v[0]}].push_back(3);
    mp[{2, v[0]}].push_back(1);
    cout << "State\t" << v[0] << '\t'<< v[1] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if (i == n - 1) cout << "*";
        cout << i << '\t';
        for (auto e : v) {
            if (mp.find({i, e}) != mp.end()) {
                for (auto ee : mp[{i, e}]) cout << ee << ' ';
                cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << endl;
    }
}

void Self(auto &v) {
    int n = 3;
    map<pair<int, string>, vector<int> > mp;
    for (int i = 0; i < n; ++i) mp[{i, v[0]}].push_back(i);
    mp[{0, v[0]}].push_back(1);
    mp[{1, v[1]}].push_back(2);
    cout << "State\t" << v[0] << '\t'<< v[1] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if (i == n - 1) cout << "*";
        cout << i << '\t';
        for (auto e : v) {
            if (mp.find({i, e}) != mp.end()) {
                for (auto ee : mp[{i, e}]) cout << ee << ' ';
                cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << endl;
    }
}

auto var(auto &s) {
    vector<string> v{"eps"};
    for(int i = 0; i < s.size(); ++i) {
        if(isalpha(s[i])) v.push_back(string() + s[i]);
    }
    return v;
}

int main() {
    int t; cout << "Enter the number of expressions: "; cin >> t;
    while (t--) {
        cout << "Enter the expression: "; string s; cin >> s;
        if((s.size() == 3 and s[1] == '.') or (s.size() == 2 and s[1]!='*')) {
            vector<string> v = var(s); And(v);
        }
        else if(s.size() == 3 and s[1] == '|') {
            vector<string> v = var(s); Or(v);
        }
        else if(s.size() == 2 and s[1] == '*') {
            vector<string> v = var(s); Star(v);
        }
        else if(s.size() == 1 and islower(s[0])) {
            vector<string> v = var(s); Self(v);
        }
        else cout << "Invalid expression!\n\n";
    }
    return 0;
}
