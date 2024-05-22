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
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int x_diff = x2 - x1;
    int y_diff = y2 - y1;
    cout << x2 - y_diff << " " << y2 + x_diff << " " << x1 - y_diff << " " << y1 + x_diff << endl;
}
