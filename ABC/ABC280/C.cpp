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
    string S, T;
    cin >> S >> T;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] != T[i])
        {
            cout << i + 1;
            return 0;
        }
    }
    cout << T.size();
}