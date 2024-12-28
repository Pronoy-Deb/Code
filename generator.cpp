#include <bits/stdc++.h>
#define ll long long
using namespace std;
void Generate(ll n, ll m, ll c, int car_len)
{
    cout << n << " " << m << " " << c << endl;
    for(int i = 0; i < m; i++) cout << 800000000+rand()%(c+1) << " ";
    cout << endl;
    string car = "";
    for(int i = 0; i < car_len; i++) car += 'a' + (rand()%26);
    cout << car << endl;
    for(int i = 0;i < n; i++)
    {
        string s;
        int done = 0,freq = 10;
        while(done < m)
        {
            if(rand()%2 == 1 && freq and s.size() + car_len <= m){
                s += car;
                done += car_len;
                // freq--;
            }
            else
            {
                char c = 'a' + (rand()%26);
                // cout << (c);
                s += c;
                done++;
            }
        }
        cout << endl;
    }
}
int main()
{
    freopen("tempbuffer.txt", "w", stdout);
    int ttt = 1;// cin >> ttt;

    cout << ttt << endl;
    for(int tc = 1; tc <= ttt; tc++)
    {
        ll nm = 98050;
        ll n = 97 + (rand()%25), m = nm/n, c = 700000000 + (rand() % 7000000), car_len = m/78;
//        ll n = 4, m = 8, c = 12, car_len = 3;
        Generate(n,m,c,car_len);
    }

    return 0;
}
