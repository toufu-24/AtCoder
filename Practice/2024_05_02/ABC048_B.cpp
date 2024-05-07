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
    int a, b, x;
    cin >> a >> b >> x;
    cout << (b - a) / x + ((a % x == 0) || (b % x == 0));
    return 0;
    bool zero = (a == 0) && (b % x == 0);
    a--;
    int a_div = a / x;
    int b_div = b / x;
    cout << b_div - a_div + zero << endl;
}
