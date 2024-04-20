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
    string cum = "";
    for (int i = 3; i < 6; i++)
    {
        cum += S[i];
    }
    int a = stoi(cum);
    if (a > 349)
    {
        ok = false;
    }
    if (a == 316)
    {
        ok = false;
    }
    if (a < 1)
    {
        ok = false;
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
