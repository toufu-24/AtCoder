#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    string S;
    cin >> S;
    bool ans = true;
    if ('A' > S[0] || S[0] > 'Z')
    {
        ans = false;
    }
    if ('A' > S[S.size() - 1] || S[S.size() - 1] > 'Z')
    {
        ans = false;
    }
    if (S.size() != 8)
    {
        ans = false;
    }
    for (int i = 1; i < S.size() - 1; i++)
    {
        if ('0' > S[i] || S[i] > '9')
        {
            ans = false;
        }
    }
    if (S[1] == '0')
    {
        ans = false;
    }
    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}