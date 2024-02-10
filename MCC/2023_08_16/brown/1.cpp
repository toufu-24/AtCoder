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
    ll K;
    cin >> K;
    vector<int> bits;
    while (K > 0)
    {
        bits.push_back(K % 2);
        K /= 2;
    }
    reverse(bits);
    for (int i = 0; i < bits.size(); i++)
    {
        if (bits[i] == 1)
        {
            cout << 2;
        }
        else
        {
            cout << 0;
        }
    }
}