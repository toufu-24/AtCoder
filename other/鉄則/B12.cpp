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
    int N;
    cin >> N;
    ld over = N;
    ld lower = 0;
    while (over - lower > 1e-10)
    {
        ld mid = (over + lower) / 2;
        if (pow(mid, 3) + mid >= N)
        {
            over = mid;
        }
        else
        {
            lower = mid;
        }
    }
    cout << fixed << setprecision(10) << over;
}