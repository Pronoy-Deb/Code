https://leetcode.com/problems/sliding-window-maximum/description/

auto wmx1d(auto &v, int k) {
    deque<pair<int, int>> mq;
    auto add = [&](int val, int in) {
        while (!mq.empty() && mq.back().first <= val) mq.pop_back();
        mq.push_back({val, in});
    };
    auto rem = [&](int in){
        if (!mq.empty() && mq.front().second == in) mq.pop_front();
    };
    for (int i = 0; i < k; ++i) add(v[i], i);
    int n = v.size(); vector<int> res(n - k + 1); res[0] = mq.front().first;
    for (int i = k; i < n; ++i) {
        rem(i - k); add(v[i], i); res[i - k + 1] = mq.front().first;
    }
    return res;
}

// OR,

auto wmx1d(auto &v, int k) {
	int n = v.size(); vector<int> res(n - k + 1); deque<int> mq;
	for (int i = 0; i < n; ++i) {
		while (!mq.empty() && v[mq.back()] <= v[i]) mq.pop_back();
		mq.push_back(i); if (mq.front() <= i - k) mq.pop_front();
		if (i + 1 >= k) res[i - k + 1] = v[mq.front()];
	}
	return res;
}

auto wmx2d(auto &v, int k, int l) {
	int n = v.size(), m = v[0].size();
    vector<vector<int>> res(m - l + 1, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		auto tmp = wmx1d(v[i], l);
		for (int j = 0; j < m - l + 1; ++j) res[j][i] = tmp[j];
	}
	vector<vector<int>> ans(n - k + 1, vector<int>(m - l + 1));
	for (int j = 0; j < m - l + 1; ++j) {
		auto tmp = wmx1d(res[j], k);
		for (int i = 0; i < n - k + 1; ++i) ans[i][j] = tmp[i];
	}
	return ans;
}


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

