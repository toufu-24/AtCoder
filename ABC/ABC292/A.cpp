#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
using ll = long long;

int main()
{
    string S;
    cin >> S;
    for (int i = 0; i < S.size(); i++)
    {
        if ('a' < S[i] < 'z')
        {
            S[i] = S[i] + 'A' - 'a';
        }
    }
    cout << S;
}