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
    string T;
    cin >> S >> T;
    for (int i = 0; i < 2; i++)
    {
        S[i] -= 'A';
        T[i] -= 'A';
    }
    int S_dist = abs(S[0] - S[1]);
    int T_dist = abs(T[0] - T[1]);
    if (5 - S_dist < S_dist)
    {
        S_dist = 5 - S_dist;
    }
    if (5 - T_dist < T_dist)
    {
        T_dist = 5 - T_dist;
    }
    if (S_dist == T_dist)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}