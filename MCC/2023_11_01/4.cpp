#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<set<int>> children;
vector<vector<int>> G;

void dfs(int now, set<int> st)
{
    for (auto next : G[now])
    {
        if (st.count(next))
        {
            continue;
        }
        st.insert(next);
        dfs(next, st);
    }
    st.erase(now);
    children[now] = st;
}

int main()
{
    int N;
    cin >> N;
    children.resize(N);
    G.resize(N);
    for (int i = 0; i < N; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(0, set<int>());
}