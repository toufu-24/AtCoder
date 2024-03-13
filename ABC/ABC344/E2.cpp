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
    int N;
    cin >> N;
    vector<int> A(N);
    map<ld, int> idx_val;
    map<int, ld> val_idx;

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        idx_val[(i + 1) * 100000000000] = A[i];
        val_idx[A[i]] = (i + 1) * 100000000000;
    }

    int Q;
    cin >> Q;
    while (Q--)
    {
        int q;
        cin >> q;
        int x, y;
        ld idx_x;
        ld idx_x_1_key;
        ld idx_y;
        auto idx_val_it = idx_val.begin();
        switch (q)
        {
        case 1:
            cin >> x >> y;
            idx_x = val_idx[x];
            idx_val_it = idx_val.find(val_idx[x]);
            if (idx_val_it == idx_val.begin() && idx_val.size() == 1)
            {
                idx_x_1_key = idx_x + 100000000000;
            }
            else if (idx_val_it == prev(idx_val.end()))
            {
                idx_x_1_key = idx_x + 100000000000;
            }
            else
            {
                idx_x_1_key = next(idx_val_it)->first;
            }
            idx_y = idx_x_1_key - 1;
            idx_val[idx_y] = y;
            val_idx[y] = idx_y;
            break;
        case 2:
            cin >> x;
            idx_x = val_idx[x];
            idx_val.erase(idx_x);
            val_idx.erase(x);
            break;
        }
    }
    for (auto i : idx_val)
    {
        cout << i.second << " ";
    }
}