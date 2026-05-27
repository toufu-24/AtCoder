#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    string s, t;
    cin >> s >> t;
    // vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
    // i 文字一致が何個あるか
    vector<int> dp(t.size() + 2, 0);
    for (int i = 0; i < s.size(); i++) {
        auto c = s[i];
        for (int j = t.size() - 1; j >= 0; j--) {
            if (t[j] == c) {
                dp[j] += dp[j - 1];
            }
        }
    }
}
