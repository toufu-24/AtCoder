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
    vector<vector<int>> need_read(N);
    vector<int> ans;
    for (int i = 0; i < N; i++)
    {
        int C;
        cin >> C;
        need_read[i].resize(C);
        for (int j = 0; j < C; j++)
        {
            cin >> need_read[i][j];
            need_read[i][j]--;
        }
    }

    queue<int> q;
    q.push(0);
    vector<bool> visited(N, false);
    visited[0] = true;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (auto next : need_read[now])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
                ans.push_back(next);
            }
        }
    }
    reverse(ans);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] + 1 << " ";
    }
}