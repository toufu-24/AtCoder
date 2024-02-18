#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int ans = 0;
    queue<pair<int, set<int>>> q;
    q.push({0, {0}});
    while (!q.empty())
    {
        auto [now, visited] = q.front();
        q.pop();
        for (auto next : G[now])
        {
            if (visited.count(next))
                continue;
            visited.insert(next);
            if (visited.size() == N)
            {
                ans++;
                continue;
            }
            q.push({next, visited});
            visited.erase(next);
        }
    }
    cout << ans;
}