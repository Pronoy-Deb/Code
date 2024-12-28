#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll B[1000000];

vector<int> crt_lps(string s)
{
    vector<int> lps(s.size(),0);
    for(int i = 0,j = 1; j < s.size(); j++)
    {
	if(s[i] == s[j]) lps[j] = i+1,i++;
	else if(i > 0) i = lps[i-1],j--;
    }
    return lps;
}
ll ScoreKMP(string s,string p)
{
    ll score = 0;
    int last_pos;
    vector<int> lps = crt_lps(p);
    for(int i = 0,j = 0; j < s.size(); j++)
    {
    	if(p[i] == s[j]) i++;
    	else if(i > 0) i = lps[i-1],j--;
    	if(i == p.size()) i = lps[i-1],last_pos  = j - p.size() + 2, score += B[last_pos-1];
    }
    return score;
}
int main()
{
    freopen("input0.txt", "r", stdin);
    freopen("output0.txt", "w", stdout);
    int ttt = 1; cin >> ttt;
    for(int tc = 1; tc <= ttt; tc++)
    {
        cout << "Case " << tc << ": ";
        ll n, m, c;
        string car;
        bool flag = 0;
        cin >> n >> m >> c;
        for(int i = 0; i < m; i++) cin >> B[i];
        cin >> car;
        for(int i = 0; i < n; i++)
        {
            string temp; cin >> temp;
            //cout << ScoreKMP(temp,car) << endl;
            if(ScoreKMP(temp,car) >= c) flag = 1;
        }
        cout << (flag ? "Yes" : "No") << endl;
    }

    return 0;
}
