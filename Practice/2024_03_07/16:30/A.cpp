#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    map<string, int> mp;
    mp["Monday"] = 5;
    mp["Tuesday"] = 4;
    mp["Wednesday"] = 3;
    mp["Thursday"] = 2;
    mp["Friday"] = 1;
    cout << mp[S];
}