#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N, M;
    cin >> N >> M;
    dsu d(M);
    vector<vector<int>> A(M);
    vector<pair<int, int>> C(M);
    map<int, set<int>> mp;
    set<int> include;
    for (int i = 0; i < M; i++)
    {
        int k, c;
        cin >> k >> c;
        A[i].resize(k);
        for (int j = 0; j < k; j++)
        {
            cin >> A[i][j];
            A[i][j]--;
            include.insert(A[i][j]);
            for (auto x : mp[A[i][j]])
            {
                d.merge(x, i);
            }
            mp[A[i][j]].insert(i);
        }
        C[i] = {c, i};
    }
    if (d.groups().size() > 1 || include.size() < N)
    {
        cout << -1 << endl;
        return 0;
    }
    if (M == 1)
    {
        cout << C[0].first * (N - 1) << endl;
        return 0;
    }
    // 連結のはず
    SORT(C);

    int ans = 0;
    dsu d2(N);
    // クラスカル法で最小全域木を求める
    for (int i = 0; i < M; i++)
    {
        int c = C[i].first;
        int idx = C[i].second;
        for (int j = 0; j < A[idx].size(); j++)
        {
            for (int k = 0; k < A[idx].size(); k++)
            {
                if (j == k)
                {
                    continue;
                }
                if (d2.same(A[idx][j], A[idx][k]))
                {
                    continue;
                }
                d2.merge(A[idx][j], A[idx][k]);
                ans += c;
            }
        }
    }

    cout << ans << endl;
}
