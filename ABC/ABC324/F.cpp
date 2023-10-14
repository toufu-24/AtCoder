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
    vector<vector<pair<int, int>>> beatiful(N);
    vector<vector<pair<int, int>>> cost(N);
    for (int i = 0; i < M; i++)
    {
        int u, v, b, c;
        cin >> u >> v >> b >> c;
        u--;
        v--;
        beatiful[u].push_back(make_pair(v, b));
        beatiful[v].push_back(make_pair(u, b));
    }
}