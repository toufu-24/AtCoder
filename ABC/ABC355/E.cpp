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

int32_t main()
{
    int N, L, R;
    cin >> N >> L >> R;

    auto query = [](int l, int r) -> int
    {
        cout << "? " << l << " " << r << endl;
        int res;
        cin >> res;
        return res;
    };

    modint::set_mod(100);
    modint ans = 0;
    int now = L;
    while (now <= R)
    {
        int max_r = -1;
        int best_i = -1, best_j = -1;
        for (int i = 0; (1 << i) <= now; i++)
        {
            int j = now - (1 << i);
            j = max(1L, j);
            int r = (1 << i) * (j + 1) - 1;
            if (r > max_r && r <= R)
            {
                max_r = r;
                best_i = i;
                best_j = j;
            }
        }
        if (best_i == -1 || best_j == -1)
        {
            break;
        }
        ans += query(best_i, best_j);
        now = max_r + 1;
    }
    cout << "! " << ans.val() << endl;
}
