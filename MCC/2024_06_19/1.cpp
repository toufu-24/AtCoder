#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    bool ok = true;
    int b = -1;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'B')
        {
            if (b != -1)
            {
                if (b % 2 == i % 2)
                {
                    ok = false;
                    break;
                }
            }
            else
            {
                b = i;
            }
        }
    }
    int R = -1;
    int K = -1;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'K')
        {
            if (K == -1)
            {
                K = i;
                if (R == -1)
                {
                    ok = false;
                }
            }
        }
        if (S[i] == 'R')
        {
            if (R == -1)
            {
                R = i;
            }
            else
            {
                if (K == -1)
                {
                    ok = false;
                }
            }
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
