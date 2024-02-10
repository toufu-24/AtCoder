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
    int K;
    cin >> K;
    ll sum = 0;
    for (int a = 1; a <= K; a++)
    {
        for (int b = 1; b <= K; b++)
        {
            for (int c = 1; c <= K; c++)
            {
                sum += gcd(gcd(a, b), c);
            }
        }
    }
    cout << sum;
}