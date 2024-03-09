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

vector<vector<string>> S;

int32_t main()
{
    string T;
    cin >> T;
    int N;
    cin >> N;
    S.resize(N);
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        S[i].resize(a);
        for (int j = 0; j < a; j++)
        {
            cin >> S[i][j];
        }
    }

    int ans = 1e18;
    string s = "";
    queue<tuple<string, int, int>> que;
    que.push({s, 0, 0});
    vector<set<string>> visited(N + 1);
    while (!que.empty())
    {
        string now;
        int depth;
        int cnt;
        tie(now, depth, cnt) = que.front();
        que.pop();
        if (depth == S.size())
        {
            if (T == now)
            {
                ans = min(ans, cnt);
            }
            continue;
        }
        for (int j = 0; j < S[depth].size(); j++)
        {
            string tmp = now + S[depth][j];
            if (visited[depth].count(tmp))
            {
                continue;
            }
            if (T.starts_with(tmp))
            {
                que.push({tmp, depth + 1, cnt + 1});
                visited[depth].insert(tmp);
            }
        }
        que.push({now, depth + 1, cnt});
    }
    cout << (ans == 1e18 ? -1 : ans) << endl;
}