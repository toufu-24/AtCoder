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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> takahashi(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        takahashi[a - 1].push_back(b - 1);
    }
    vector<set<int>> himo(N);
    for (int i = 0; i < N; i++)
    {
        himo[i].insert(takahashi[i].size());
    }

    vector<vector<int>> aoki(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        aoki[a - 1].push_back(b - 1);
    }

    queue<int> q;
    for (int i = 0; i < N; i++)
    {
        q.push(i);
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            for (auto next : takahashi[now])
            {
                if (himo[next].count(himo[now].size()))
                {
                    himo[next].insert(himo[now].size());
                    q.push(next);
                }
            }
        }
    }
}