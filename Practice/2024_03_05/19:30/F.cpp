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

#define check(x) \
    if (x <= 0)  \
        continue;

int main()
{
    vector<int> h(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> h[i];
    }
    vector<int> w(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> w[i];
    }

    int ans = 0;
    for (int i = 1; i <= 30; i++)
    {
        for (int j = 1; j <= 30; j++)
        {
            int k = w[0] - i - j;
            check(k);
            for (int l = 1; l <= 30; l++)
            {
                for (int m = 1; m <= 30; m++)
                {
                    int n = w[1] - l - m;
                    check(n);
                    int o = h[0] - i - l;
                    check(o);
                    int p = h[1] - j - m;
                    check(p);

                    if (h[2] - k - n == w[2] - o - p && w[2] - o - p > 0)
                    {
                        ans++;
                        // cerr << i << " " << j << " " << k << endl;
                        // cerr << l << " " << m << " " << n << endl;
                        // cerr << o << " " << p << " " << h[2] - k - n << endl;
                        // cerr << endl;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}