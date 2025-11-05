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
    int n, k;
    cin >> n >> k;
    int r, s, p;
    cin >> r >> s >> p;
    string t;
    cin >> t;
    vector<int> tint(n);
    for (int i = 0; i < n; i++) {
        switch (t[i]) {
        case 'R':
            tint[i] = 0;
            break;
        case 'S':
            tint[i] = 1;
            break;
        case 'P':
            tint[i] = 2;
            break;
        default:
            break;
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    int k_sum = 0;
    for (int i = 0; i <= n; i++) {
        dp[i + ]
    }
}
