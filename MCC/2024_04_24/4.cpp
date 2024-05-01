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
    int K;
    cin >> K;
    if (K < 10)
    {
        cout << K << endl;
        return 0;
    }
    int now = 9;
    int keta = 1;
    while (now * 25 < K)
    {
        now *= 25;
        keta++;
    }
    K -= now;
}
