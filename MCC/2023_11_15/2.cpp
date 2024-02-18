#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    string left = "";
    int remove_idx = N;
    for (int q = 0; q < Q; q++)
    {
        int t, x;
        cin >> t >> x;
        string tmp;
        switch (t)
        {
        case 1:
            remove_idx -= x;
            if (remove_idx < 0)
            {
                remove_idx += N;
            }
            break;
        case 2:
            cout << S[(remove_idx + x - 1) % N] << endl;
            break;
        default:
            break;
        }
    }
}