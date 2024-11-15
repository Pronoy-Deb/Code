#include<bits/stdc++.h>
using namespace std;
void And(auto &v) {
    int n = 4; map<pair<int, string>, vector<int>> st;
    for (int i = 0; i < n; ++i) st[{i, v[0]}].push_back(i);
    st[{0, v[1]}].push_back(1); st[{1, v[0]}].push_back(2);
    st[{2, v[2]}].push_back(3); cout << "State\t" << v[0]
    << '\t'<< v[1] << '\t' << v[2] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if(i == n-1) cout << "*"; cout << i << '\t';
        for (auto e : v) {
            if (st.find({i, e}) != st.end()) {
                for (auto ee : st[{i, e}])
                    cout << ee << ' '; cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << '\n';
    }
}
void Or(auto &v) {
    int n = 6; map<pair<int, string>, vector<int> > st;
    for (int i = 0; i < n; ++i) st[{i, v[0]}].push_back(i);
    st[{0, v[0]}].push_back(1); st[{0, v[0]}].push_back(2);
    st[{1, v[1]}].push_back(3); st[{2, v[2]}].push_back(4);
    st[{3, v[0]}].push_back(5); st[{4, v[0]}].push_back(5);
    cout << "State\t" << v[0] << '\t' << v[1] << '\t'
    << v[2] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if(i==n-1) cout << "*"; cout << i << '\t';
        for (auto e : v) {
            if (st.find({i, e}) != st.end()) {
                for (auto ee : st[{i, e}])
                    cout << ee << ' '; cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << '\n';
    }
}
void Star(auto &v) {
    int n = 4; map<pair<int, string>, vector<int> > st;
    for (int i = 0; i < n; ++i) st[{i, v[0]}].push_back(i);
    st[{0, v[0]}].push_back(1); st[{0, v[0]}].push_back(3);
    st[{1, v[1]}].push_back(2); st[{2, v[0]}].push_back(3);
    st[{2, v[0]}].push_back(1);
    cout << "State\t" << v[0] << '\t'<< v[1] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if(i==n-1) cout << "*"; cout << i << '\t';
        for (auto e : v) {
            if (st.find({i, e}) != st.end()) {
                for (auto ee : st[{i, e}])
                    cout << ee << ' '; cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << '\n';
    }
}
void Self(auto &v) {
    int n = 3; map<pair<int, string>, vector<int> > st;
    for (int i = 0; i < n; ++i) st[{i, v[0]}].push_back(i);
    st[{0, v[0]}].push_back(1); st[{1, v[1]}].push_back(2);
    cout << "State\t" << v[0] << '\t'<< v[1] << '\n';
    for (int i = 0; i < n; ++i) {
        if (!i) cout << "->";
        else if(i==n-1) cout << "*"; cout << i << '\t';
        for (auto e : v) {
            if (st.find({i, e}) != st.end()) {
                for (auto ee : st[{i, e}])
                    cout << ee << ' '; cout << '\t';
            }
            else cout << '-' << '\t';
        }
        cout << '\n';
    }
}
auto var(auto &s) {
    vector<string> v{"eps"};
    for(int i = 0; i < s.size(); ++i) {
        if(s[i]>='a' && s[i]<='z') {
            string r; r+=s[i]; v.push_back(r);
        }
    }
    return v;
}
int main() {
    cout << "Enter the number of expressions: ";
    int t; cin >> t;
    while (t--) {
        cout<<"Enter the expression: "; string s; cin>>s;
        if((s.size() == 3 && s[1] == '.') or (s.size()==2
        && s[1]!='*')) {
            vector<string> v = var(s); And(v);
        }
        else if(s.size() == 3 && s[1] == '|') {
            vector<string> v = var(s); Or(v);
        }
        else if(s.size() == 2 && s[1] == '*') {
            vector<string> v = var(s); Star(v);
        }
        else if(s.size() == 1 && s.front() >= 'a'
        && s.front() <= 'z') {
            vector<string> v = var(s); Self(v);
        }
        else cout << "Invalid expression!\n";
        cout << '\n';
    }
    return 0;
}







