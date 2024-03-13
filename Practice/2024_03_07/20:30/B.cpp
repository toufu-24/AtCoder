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
    string S;
    cin >> S;
    bool yes = true;
    for (int i = 1; i < 16; i += 2)
    {
        if (S[i] != '0')
        {
            yes = false;
            break;
        }
    }
    if (yes)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}