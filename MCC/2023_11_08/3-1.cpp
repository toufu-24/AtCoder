#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> AB(N);
    for (int i = 0; i < N; i++)
    {
        cin >> AB[i].first >> AB[i].second;
    }
    SORT(AB);
    map<int, int> sum;
    for (int i = 0; i < N; i++)
    {
        sum[AB[i].first]++;
        sum[AB[i].first + AB[i].second]--;
    }
    vector<int> ans(N + 1, 0);
    int now = 0;
    int prev = 0;
    for (auto &[x, change] : sum)
    {
        ans[now] += x - prev;
        now += change;
        prev = x;
    }
    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << " ";
    }
}