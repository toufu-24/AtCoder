#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string S;
    cin >> S;
    int N = S.size();
    bool er = false;
    string judge;
    judge += S[N - 2];
    judge += S[N - 1];
    if (judge == "er")
    {
        cout << "er";
    }
    else
    {
        cout << "ist";
    }
}