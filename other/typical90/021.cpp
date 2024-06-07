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
    scc_graph g(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g.add_edge(a, b);
    }

    auto scc = g.scc();
    int ans = 0;
    for (int i = 0; i < scc.size(); i++)
    {
        ans += scc[i].size() * (scc[i].size() - 1) / 2;
    }
    cout << ans << endl;
}
