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
// https://algo-logic.info/run-length/
/* encode: ランレングス圧縮を行う
 */
vector<pair<char, int>> encode(const string &str) {
    int n = (int)str.size();
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++) {
        };
        ret.push_back({str[l], r - l});
        l = r;
    }
    return ret;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        auto run = encode(s);
        int ans = 0;
        int now_cost = 0;
        for (auto [c, cnt] : run) {
            if (c == '0') {
                now_cost += cnt;
            }
        }
        int left = 0, right = run.size() - 1;
    }
}