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
    ll N;
    cin >> N;

    while (N % 2 == 0)
    {
        N /= 2;
    }
    while (N % 3 == 0)
    {
        N /= 3;
    }

    if (N != 1)
        cout << "No" << endl;
    else
        cout << "Yes" << endl;
}