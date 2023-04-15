#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    string S;
    cin >> S;
    int B1, B2;
    bool ans1 = false, ans2 = false;
    bool flg = false;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'B')
        {
            if (!flg)
            {
                B1 = i;
                flg = true;
            }
            else
            {
                B2 = i;
            }
        }
    }
    if (B1 % 2 != B2 % 2)
    {
        ans1 = true;
    }
    bool r = false;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == 'R' && !r)
        {
            r = true;
        }
        else if (S[i] == 'R' && r)
        {
            r = false;
        }
        if (r)
        {
            if (S[i] == 'K')
            {
                ans2 = true;
            }
        }
    }
    if (ans1 && ans2)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}