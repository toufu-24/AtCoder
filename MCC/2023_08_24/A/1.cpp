#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N;
    cin >> N;
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        int n = b - a + 1;
        sum += n * (2 * a + (n - 1)) / 2;
    }
    cout << sum << endl;
}