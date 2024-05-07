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
    // 連結のはず

    set<int> used;
    int ans = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto [from, cost] = pq.top();
        pq.pop();
        if (used.contains(from))
        {
            continue;
        }
        used.insert(from);
        ans += cost;
        for (auto to : mp[from])
        {
            for (auto x : A[to])
            {
                if (!used.contains(x))
                {
                    pq.push({x, C[to].first});
                }
            }
        }
    }
    cout << ans << endl;
}
