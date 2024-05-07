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

#define int ll

int32_t main()
{
    int N, Q;
    cin >> N >> Q;
    vector<map<int, int>> C(N);
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        C[i][tmp]++;
    }

    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (C[a].size() > C[b].size())
        {
            swap(C[a], C[b]);
        }
        for (auto [key, val] : C[a])
        {
            C[b][key] += val;
        }
        C[a].clear();
        cout << C[b].size() << endl;
    }
}
