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
    string S;
    cin >> S;
    map<char, int> mp;
    mp['v'] = 1;
    mp['w'] = 2;
    int ans = 0;
    for (int i = 0; i < S.size(); i++)
    {
        ans += mp[S[i]];
    }
    cout << ans << endl;
}