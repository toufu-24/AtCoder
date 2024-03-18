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

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    bool ok = true;
    if (S[0] != '<')
    {
        ok = false;
    }
    if (S[S.size() - 1] != '>')
    {
        ok = false;
    }
    for (int i = 1; i < S.size() - 1; i++)
    {
        if (S[i] != '=')
        {
            ok = false;
        }
    }
    if (ok)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}