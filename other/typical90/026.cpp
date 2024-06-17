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
    vector<vector<int>> G(N);
    vector<int> A(N - 1), B(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }
    // 葉からスタートしていこう
    int start = 0;
    for (int i = 0; i < N; i++)
    {
        if (G[i].size() == 1)
        {
            start = i;
            break;
        }
    }

    queue<int> q;
    q.push(start);
    vector<bool> visited(N, false);
    visited[start] = true;
    vector<int> color(N, -1);
    color[start] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        int now_color = color[now];
        for (auto next : G[now])
        {
            if (visited[next])
            {
                continue;
            }
            visited[next] = true;
            color[next] = 1 - now_color;
            q.push(next);
        }
    }
    vector<int> zero, one;
    for (int i = 0; i < N; i++)
    {
        if (color[i] == 0)
        {
            zero.push_back(i);
        }
        else
        {
            one.push_back(i);
        }
    }

    vector<int> ans;
    if (zero.size() >= N / 2)
    {
        ans.insert(ans.end(), all(zero));
    }
    else
    {
        ans.insert(ans.end(), all(one));
    }

    for (int i = 0; i < N / 2; i++)
    {
        cout << ans[i] + 1 << " ";
    }
}
