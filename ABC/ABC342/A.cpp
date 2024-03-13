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
    char f = S[0];
    char s = S[1];
    if (f != s)
    {
        char t = S[2];
        if (t == f)
        {
            cout << 2;
            return 0;
        }
        else
        {
            cout << 1;
            return 0;
        }
    }
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] != f)
        {
            cout << i + 1;
            return 0;
        }
    }
}