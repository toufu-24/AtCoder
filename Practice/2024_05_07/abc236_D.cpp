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
vector<vector<int>> A;
int dfs(int v, set<int> unused, int xor_num, int depth)
{
    if (unused.size() == 0)
    {
        return xor_num;
    }
    int res = 0;
    for (auto u : unused)
    {
        unused.erase(u);
        if ((depth + 1) % 2 == 0)
        {
            res = max(res, dfs(u, unused, xor_num ^ A[v][u], depth + 1));
        }
        else
        {
            res = min(res, dfs(u, unused, xor_num, depth + 1));
        }
        unused.insert(u);
    }
    return res;
}

int32_t main()
{
    int N;
    cin >> N;
    A.resize(2 * N, vector<int>(2 * N, 0));
    for (int i = 0; i < 2 * N; i++)
    {
        for (int j = i + 1; j < 2 * N; j++)
        {
            cin >> A[i][j];
            A[j][i] = A[i][j];
        }
    }

    int ans = 0;
    set<int> st;
    for (int i = 0; i < 2 * N; i++)
    {
        st.insert(i);
    }
    for (int i = 0; i < 2 * N; i++)
    {
        st.erase(i);
        ans = max(ans, dfs(i, st, 0, 1));
        st.insert(i);
    }
    cout << ans << endl;
}
