#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct monotonous_queue
{ // max, stores strictly decreasing sequence of the current queue
    int ar[N + 10], b[N + 10], l = 0, r = -1;
    void push(int val)
    {
        int cnt = 0;
        while (l <= r && ar[r] <= val)
        {
            cnt += b[r] + 1;
            r--;
        }
        ar[++r] = val, b[r] = cnt;
    };
    int top()
    {
        return ar[l];
    }
    void pop()
    {
        if (l > r)
            return;
        if (b[l] > 0)
        {
            b[l]--;
            return;
        }
        l++;
    }
};

int32_t main()
{

    return 0;
}