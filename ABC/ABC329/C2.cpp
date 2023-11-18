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
    int N;
    cin >> N;
    string S;
    cin >> S;
    map<char, int> mp;
    int now_renzoku = 1;
    char now = S[0];
    for (int i = 1; i < N; i++)
    {
        if (S[i] == now)
        {
            now_renzoku++;
        }
        else
        {
            mp[now] = max(mp[now], now_renzoku);
            now_renzoku = 1;
            now = S[i];
        }
    }
    mp[now] = max(mp[now], now_renzoku);
    int ans = 0;
    for (auto i : mp)
    {
        ans += i.second;
    }
    cout << ans << endl;
}