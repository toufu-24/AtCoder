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
    int N, M;
    cin >> N >> M;
    vector<int> X(M);
    for (int i = 0; i < M; i++)
    {
        cin >> X[i];
        X[i]--;
    }

    vector<int> dist(M - 1);
    vector<bool> is_looped(M - 1);
    for (int i = 0; i < M - 1; i++)
    {
        int dist1 = abs(X[i + 1] - X[i]);
        int dist2 = abs(N - X[i + 1] + X[i]);
        if (dist1 < dist2)
        {
            dist[i] = dist1;
            is_looped[i] = false;
        }
        else
        {
            dist[i] = dist2;
            is_looped[i] = true;
        }
    }
    int origin_dist = accumulate(all(dist), 0);

    int ans = 1e18;
    int now = origin_dist;
    // 差分を利用して最小値を求める
    for (int i = 0; i < M - 1; i++)
    {
        int tmp = origin_dist;
        if (is_looped[i])
        {
            tmp -= dist[i];
            tmp += abs(N - X[i + 1] + X[i]);
        }
        else
        {
            tmp -= dist[i];
            tmp += abs(X[i + 1] - X[i]);
        }
        ans = min(ans, tmp);
    }

    cout << ans << endl;
}