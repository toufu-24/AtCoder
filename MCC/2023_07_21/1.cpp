#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    ld A, B, C, X;
    cin >> A >> B >> C >> X;
    if (X <= A)
    {
        cout << 1;
        return 0;
    }
    if (X > B)
    {
        cout << 0;
        return 0;
    }
    cout << C / (B - A);
}