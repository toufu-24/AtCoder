#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> hashigo(N);
    unordered_map<int, vector<int>> G;
    for (int i = 0; i < N; i++)
    {
        cin >> hashigo[i].first >> hashigo[i].second;
        G[hashigo[i].first].push_back(hashigo[i].second);
        G[hashigo[i].second].push_back(hashigo[i].first);
    }

    int max = -1;
    vector<bool> gone(2e9 + 1, false);
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int now = q.front();
        if (now > max)
        {
            max = now;
        }
        q.pop();
        for (auto next : G[now])
        {
            if (gone[next])
            {
                continue;
            }
            gone[next] = true;
            q.push(next);
        }
    }

    cout << max;
}