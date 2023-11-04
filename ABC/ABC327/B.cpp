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
    ll B;
    cin >> B;
    for (ll i = 1; pow(i, i) <= B + 10; i++)
    {
        if (pow(i, i) == B)
        {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}