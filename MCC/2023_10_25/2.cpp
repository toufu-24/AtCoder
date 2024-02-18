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
    int N, X, Y;
    cin >> N >> X >> Y;

    map<int, int> red;
    red[N] = 1;
    map<int, int> blue;

    int now = N;
    while (now != 1)
    {
        int r = red[now];
        red[now - 1] += r;
        blue[now] += X * r;
        red.erase(now);
        int b = blue[now];
        red[now - 1] += b;
        blue[now - 1] += Y * b;
        blue.erase(now);
        now--;
    }
    cout << blue[1];
}