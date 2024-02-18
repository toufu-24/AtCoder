#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    set<string> S = {"ABC", "ARC", "AGC", "AHC"};
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        S.erase(s);
    }
    cout << *begin(S);
}