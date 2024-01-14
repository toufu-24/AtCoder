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

int main()
{
    int N;
    cin >> N;
    bitset<32> b(N);
    int ans = 0;
    for (int i = 0; i < 32; i++)
    {
        if (b[i] == 1)
        {
            ans = i;
            break;
        }
    }

    cout << ans << endl;
}