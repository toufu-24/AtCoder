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
    vector<int> H(N);
    for (int i = 0; i < N; i++)
    {
        cin >> H[i];
    }
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    set<int> ans;
    for (int start = 0; start < N; start++)
    {
        int max_H = start;
        for (auto v : graph[start])
        {
            if (H[max_H] <= H[v])
            {
                max_H = v;
            }
        }
        if (max_H == start)
            ans.insert(max_H);
    }
    cout << ans.size();
}