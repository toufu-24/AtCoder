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
    queue<vector<int>> q;
    for (int i = 1; i <= M; i++)
    {
        q.push({i});
    }

    vector<vector<int>> ans;
    while (!q.empty())
    {
        auto v = q.front();
        q.pop();
        if (v.size() == N)
        {
            ans.push_back(v);
            continue;
        }
        for (int i = v.back() + 1; i <= M; i++)
        {
            auto u = v;
            u.push_back(i);
            q.push(u);
        }
    }
    SORT(ans);
    for (auto v : ans)
    {
        for (int i = 0; i < N; i++)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}
