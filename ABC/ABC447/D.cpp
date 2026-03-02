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
    string s;
    cin >> s;

    int n = s.size();
    // ABCに対してそれぞれどの段階にいけてるか
    // vector<vector<int>> dp(3, vector<int>(3, 0));
    vector<int> dp(3, 0);

    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            dp[0]++;
        } else if (s[i] == 'B') {
            if (dp[0] >= 1) {
                dp[1]++;
                dp[0]--;
            }
        } else if (s[i] == 'C') {
            if (dp[1] >= 1) {
                dp[2]++;
                dp[1]--;
            }
        }
    }

    cout << dp[2] << endl;
}
