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
    for (int i = 0; i < 8; i++)
    {
        string S;
        cin >> S;
        for (int j = 0; j < 8; j++)
        {
            if (S[j] == '*')
            {
                cout << char('a' + j) << 8 - i;
                return 0;
            }
        }
    }
}