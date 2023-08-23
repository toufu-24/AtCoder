#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<vector<int>> need_read;
vector<bool> visited;
vector<int> ans;

void dfs(int now)
{
    visited[now] = true;
    for (auto next : need_read[now])
    {
        if (!visited[next])
        {
            dfs(next);
            ans.push_back(next);
        }
    }
}

int main()
{
    int N;
    cin >> N;
    need_read.resize(N);
    visited.assign(N, false);
    ans.clear();

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

    dfs(0);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] + 1 << " ";
    }
}
