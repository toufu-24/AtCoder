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
    string S;
    cin >> S;
    bool ok = true;
    if (islower(S[0]))
    {
        ok = false;
    }
    for (int i = 1; i < S.size(); i++)
    {
        if (isupper(S[i]))
        {
            ok = false;
            break;
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