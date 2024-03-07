#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    bitset<64> b(N);
    int cnt = 0;
    for (int i = 0; i < 64; i++)
    {
        if (b[i])
        {
            break;
        }
        cnt++;
    }
    cout << cnt << endl;
}