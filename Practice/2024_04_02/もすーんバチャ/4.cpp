#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, M, L;
    cin >> N >> M >> L;
    vector<int> a(N), b(M);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> b[i];
    }
    vector<set<int>> bad(N);
    vector<pair<int, int>> cd(L);
    for (int i = 0; i < L; i++)
    {
        cin >> cd[i].first >> cd[i].second;
        cd[i].first--;
        cd[i].second--;
        bad[cd[i].first].insert(cd[i].second);
    }
    vector<pair<int, int>> a_idx(N), b_idx(M);
    for (int i = 0; i < N; i++)
    {
        a_idx[i] = {a[i], i};
    }
    for (int i = 0; i < M; i++)
    {
        b_idx[i] = {b[i], i};
    }
    RSORT(a_idx);
    RSORT(b_idx);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // ここにはたかだかL回しか入らない
            if (bad[a_idx[i].second].count(b_idx[j].second))
            {
                continue;
            }
            ans = max(ans, a_idx[i].first + b_idx[j].first);
            break;
        }
    }
    cout << ans << endl;
}
