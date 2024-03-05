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
    set<string> contest = {"ABC", "ARC", "AGC", "AHC"};
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        contest.erase(s);
    }
    cout << *contest.begin();
}