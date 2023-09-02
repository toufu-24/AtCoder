#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> graph(N);
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        graph[i].push_back(a - 1);
    }
    vector<int> dist(N, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (auto nv : graph[v])
        {
            if (dist[nv] != -1)
                continue;
            dist[nv] = dist[v] + 1;
            if (nv == 1)
            {
                goto end;
            }
            q.push(nv);
        }
    }
end:
    cout << dist[1] << endl;
}