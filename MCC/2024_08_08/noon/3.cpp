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
    int N, X;
    cin >> N >> X;
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i];
    }

    vector<set<int>> dp(N + 1);
    dp[0].insert({0, 0});
    for (int i = 0; i < N; i++) {
        for (auto x : dp[i]) {
            dp[i + 1].insert({x + a[i]});
            dp[i + 1].insert({x + b[i]});
        }
    }

    if (dp[N].count(X)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
