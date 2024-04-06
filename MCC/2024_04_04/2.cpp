#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int Sx, Sy, Gx, Gy;
    cin >> Sx >> Sy >> Gx >> Gy;
    ld ans = 0;
    ld left = -1e18, right = 1e18;
    while (abs(right - left) > 1e-10)
    {
        ld mid = (left + right) / 2;
        // mid に当てたら，y = Gy でどうなるか
        ld a = (0 - Sy) / (mid - Sx);
        a = -a;
        ld x = Gy / a + mid;
        if (x < Gx)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    cout << fixed << setprecision(10) << left << endl;
}
