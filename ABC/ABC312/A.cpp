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
    set<string> table = {"ACE", "BDF", "CEG", "DFA", "EGB", "FAC", "GBD"};
    if (table.count(S))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}