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
    string S;
    cin >> S;
    ll K;
    cin >> K;
    int i;
    for (i = 0; S[i] == '1'; i++)
    {
        if (i == K - 1)
        {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << S[i] << endl;
}
