#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<set<string>> sto;
    set<string> st{"if", "else", "then", "for", "while",
    "int", "string", "float", "char"};
    sto.push_back(st); st.clear();
    st = {"+", "-", "*", "/", "++", "--"};
    sto.push_back(st); st.clear();
    st = {"==", ">", "<", ">=", "<=", "!="};
    sto.push_back(st); st.clear();
    st = {"&", "|", "~", "^", ">>", "<<"};
    sto.push_back(st); st.clear();
    st = {"&&", "||", "!"}; sto.push_back(st);
    st.clear();
    st = {"="}; sto.push_back(st); st.clear();
    st = {";", "(", ")"}; sto.push_back(st);
    string s, r; getline(cin, s); map<string, int> cnt;
    for (auto &e : s) {
        if (e==' ' or e=='(' or e==')' or e==';') {
            cnt[r]++; r = e; cnt[r]++; r.clear();
        } else r += e;
    }
    cnt.erase(" "); cnt.erase(cnt.begin());
    set<pair<string, int>> id, flo, in, ari, bit, rel,
    as, pun, key, log, ps;
    for (auto [f, s] : cnt) {
        bool ok = 1; for (int i = 0; i < 7; ++i) {
            if (sto[i].find(f) != sto[i].end()) {
                ok = 0; if (!i) key.insert({f, s});
                else if (i == 1) ari.insert({f, s});
                else if (i == 2) rel.insert({f, s});
                else if (i == 3) bit.insert({f, s});
                else if (i == 4) log.insert({f, s});
                else if (i == 5) as.insert({f, s});
                else ps.insert({f, s}); break;
            }
        }
        if (!ok) continue; ok = 1;
        for (auto e : f) {
            if (e==' '||e==';'||e=='('||e==')') {
                ps.insert({f, s}); ok = 0; break;
            }
            if (e >= 'a' and e <= 'z') {
                id.insert({f, s}); ok = 0; break;
            }
            if (e == '.') {
                flo.insert({f, s}); ok = 0; break;
            }
        }
        if (ok) in.insert({f, s});
    }
    cout << "IDENTIFIER:\t"; for (auto &[f, s] : id)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "Keyword:\t"; for (auto &[f, s] : key)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "OPERATOR:\nArithmetic Operator:\t";
    for (auto &[f, s] : ari)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "Relational Operator:\t";
    for (auto &[f, s] : rel)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "Assignment Operator:\t";
    for (auto &[f, s] : as)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "Bitwise Operator:\t";
    for (auto &[f, s] : bit)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "PUNCTUATION SYMBOL:\t";
    for (auto &[f, s] : ps)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "INTEGER:\t"; for (auto &[f, s] : in)
        cout << f << "(" << s << ") "; cout << '\n';
    cout << "FLOAT:\t"; for (auto &[f, s] : flo)
        cout << f << "(" << s << ") "; cout << '\n';
    return 0;
}

// if (a == b) then (c = 10 + 2 * a & d = 12.56 + 3.5 - 2);
