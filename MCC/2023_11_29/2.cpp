#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<set<int>> AB(N);
    vector<set<int>> CD(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        AB[a].insert(b);
        AB[b].insert(a);
    }
    for (int i = 0; i < M; i++)
    {
        int c, d;
        cin >> c >> d;
        c--;
        d--;
        CD[c].insert(d);
        CD[d].insert(c);
    }

    vector<int> perm(N);
    iota(all(perm), 0);
    do
    {
        bool ok = true;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (AB[i].count(j) && !CD[perm[i]].count(perm[j]))
                {
                    ok = false;
                }
                if (!AB[i].count(j) && CD[perm[i]].count(perm[j]))
                {
                    ok = false;
                }
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
