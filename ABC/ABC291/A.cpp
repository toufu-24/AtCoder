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
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] <= 'Z' && S[i] >= 'A')
        {
            cout << i + 1;
        }
    }
}