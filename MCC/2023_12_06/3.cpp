#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int K;
    cin >> K;
    modint::set_mod(K);
    int tmp = 0;
    for (int i = 0; i <= K; i++)
    {
        tmp *= 10;
        tmp += 7;
        if (tmp % K == 0)
        {
            cout << i + 1;
            return 0;
        }
        tmp %= K;
    }
    cout << -1 << endl;
}