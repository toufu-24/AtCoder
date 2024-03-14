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

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G_ab(N);
    // vector<set<int>> G_ab(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G_ab[a].push_back(b);
        G_ab[b].push_back(a);
    }
    vector<set<int>> G_cd(N);
    for (int i = 0; i < M; i++)
    {
        int c, d;
        cin >> c >> d;
        c--;
        d--;
        G_cd[c].insert(d);
        G_cd[d].insert(c);
    }
    vector<int> perm(N);
    iota(all(perm), 0);
    do
    {
        bool ok = true;
        for (int i = 0; i < N; i++)
        {
            if (G_ab[i].size() != G_cd[perm[i]].size())
            {
                ok = false;
                break;
            }
            for (int j = 0; j < G_ab[i].size(); j++)
            {
                if (!G_cd[perm[i]].count(perm[G_ab[i][j]]))
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
            {
                break;
            }
        }
        if (ok)
        {
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(all(perm)));
    cout << "No" << endl;
}