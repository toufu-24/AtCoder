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
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int min_x = min(x1, x2);
    int min_y = min(y1, y2);
    for (int i = min_x - 5; i <= min_x + 5; i++)
    {
        for (int j = min_y - 5; j <= min_y + 5; j++)
        {
            if ((x1 - i) * (x1 - i) + (y1 - j) * (y1 - j) == 5)
            {
                if ((x2 - i) * (x2 - i) + (y2 - j) * (y2 - j) == 5)
                {
                    cout << "Yes";
                    return 0;
                }
            }
        }
    }
    cout << "No";
}