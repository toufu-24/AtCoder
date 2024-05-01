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
    if (S[0] != 'A')
    {
        ok = false;
    }
    int c = 0;
    int idx = -1;
    for (int i = 2; i < S.size() - 1; i++)
    {
        if (S[i] == 'C')
        {
            c++;
            idx = i;
        }
    }
    if (c != 1)
    {
        ok = false;
    }
    for (int i = 0; i < S.size(); i++)
    {
        if (i == 0 || i == idx)
        {
            continue;
        }
        if (isupper(S[i]))
        {
            ok = false;
        }
    }
    if (ok)
    {
        cout << "AC" << endl;
    }
    else
    {
        cout << "WA" << endl;
    }
}
