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
    int Q;
    cin >> Q;
    multiset<int> A;
    while (Q--)
    {
        int c;
        cin >> c;
        int x, k;
        switch (c)
        {
        case 1:
            cin >> x;
            A.insert(x);
            break;
        case 2:
        {
            cin >> x >> k;
            auto itr = A.upper_bound(x);
            bool ok = true;
            for (int i = 0; i < k; i++)
            {
                if (itr == A.begin())
                {
                    ok = false;
                    break;
                }
                itr = prev(itr);
            }
            cout << (ok ? *itr : -1) << endl;
            break;
        }
        case 3:
        {
            cin >> x >> k;
            auto itr = A.lower_bound(x);
            bool ok = true;
            for (int i = 0; i < k - 1; i++)
            {
                if (itr == A.end())
                {
                    ok = false;
                    break;
                }
                itr = next(itr);
            }
            if (itr == A.end())
            {
                ok = false;
            }
            cout << (ok ? *itr : -1) << endl;
            break;
        }
        default:
            break;
        }
    }
}
