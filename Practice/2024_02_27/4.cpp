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
    string S_;
    cin >> S_;
    vector<int> S(S_.size());
    for (int i = 0; i < S_.size(); i++)
    {
        S[i] = S_[i] - 'A' + 1;
    }

    ll ans = 0;
    for (int i = 0; i < S.size(); i++)
    {
        ans = ans * 26 + S[i];
    }
    cout << ans << endl;
}