#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

bool is_prime(int n)
{
    if (n == 1)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int Q;
    cin >> Q;
    vector<pair<int, int>> q;
    for (int i = 0; i < Q; i++)
    {
        int l, r;
        cin >> l >> r;
        q.push_back({l, r});
    }

    vector<int> ans(1e5 + 1, 0);
    ans[3] = 1;
    ans[4] = 1;
    int cnt = 1;
    for (int i = 5; i <= 1e5; i += 4)
    {
        if (is_prime(i) && is_prime((i + 1) / 2))
        {
            cnt++;
        }
        for (int j = 0; j < 4; j++)
        {
            ans[i + j] = cnt;
        }
    }
    for (int i = 0; i < Q; i++)
    {
        cout << ans[q[i].second] - ans[q[i].first - 1] << endl;
    }
}