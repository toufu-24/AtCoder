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
    int N;
    cin >> N;
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        // i * jが平方数となる最小のjを求める
        int j = i;
        for (int k = 2; k * k <= j; k++)
        {
            while (j % (k * k) == 0)
            {
                j /= k * k;
            }
        }
        // Nを超えない個数を求める
        for (int k = 1; j * k * k <= N; k++)
        {
            ans++;
        }
    }
    cout << ans << endl;
}
