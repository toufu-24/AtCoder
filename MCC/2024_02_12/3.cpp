#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

struct edge
{
    int to;
    int color;
};

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<edge>> graph(N);
    vector<int> a(N);
    vector<int> b(N);
    for (int i = 0; i < M; i++)
    {
        int _a, _b;
        cin >> _a >> _b;
        _a--;
        _b--;
        a[i] = _a;
        b[i] = _b;
    }
    vector<int> c(N);
    for (int i = 0; i < N; i++)
    {
        int _c;
        cin >> _c;
        c[i] = _c;
    }
    for (int i = 0; i < M; i++)
    {
        graph[a[i]].push_back({b[i], c[b[i]]});
        graph[b[i]].push_back({a[i], c[a[i]]});
    }
}
