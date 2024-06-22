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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    dsu uf(N);
    vector<vector<int>> graph(N);
    // クラスカル法
    // {cost, 頂点}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < N; i++)
    {
        pq.push({A[i], i});
    }

    while (!pq.empty())
    {
        auto [cost1, v1] = pq.top();
        pq.pop();
        if (pq.empty())
            break;
        vector<pair<int, int>> tmp;
        while (!pq.empty())
        {
            auto [cost2, v2] = pq.top();
            pq.pop();
            if (uf.same(v1, v2))
            {
                tmp.push_back({cost2, v2});
                continue; 
            }
            uf.merge(v1, v2);
            graph[v1].push_back(v2);
            int size1 = graph[v1].size();
            pq.push({size1 * size1 - (size1 - 1) * (size1 - 1), v1});
            int size2 = graph[v2].size();
            pq.push({size2 * size2 - (size2 - 1) * (size2 - 1), v2});
            break;
        }
        for (auto [cost, v] : tmp)
        {
            pq.push({cost, v});
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += graph[i].size() * graph[i].size() * A[i];
    }
    cout << ans;
}
