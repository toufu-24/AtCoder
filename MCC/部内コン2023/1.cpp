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
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; i++)
    {
        int k;
        cin >> k;
        vector<int> a(k);
        for (int l = 0; l < k; l++)
        {
            cin >> a[l];
            a[l]--;
        }

        for (int l = 0; l < k; l++)
        {
            for (int j = l + 1; j < k; j++)
            {
                g[a[l]].push_back(a[j]);
                g[a[j]].push_back(a[l]);
            }
        }
    }

    queue<int> q;
    q.push(0);
    vector<int> dist(N, -1);
    dist[0] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (auto next : g[now])
        {
            if (dist[next] != -1)
                continue;
            dist[next] = dist[now] + 1;
            q.push(next);
        }
        if (dist[N - 1] != -1)
            break;
    }
    cout << dist[N - 1] - 1 << endl;
}