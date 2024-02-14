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

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        A--;
        B--;
        graph[B].push_back(A);
    }

    int ans = -1;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (graph[i].size() == 0)
        {
            ans = i + 1;
            cnt++;
        }
    }
    if (cnt == 1)
    {
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}