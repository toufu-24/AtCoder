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
    // 前に行くやつは左から，後ろに行くやつは右から
    vector<string> ans;
    vector<int> diff(s.size(), 0);
    for (int i = 0; i < s.size(); i++) {
        diff[i] = t[i] - s[i];
    }
    for (int i = 0; i < s.size(); i++) {
        if (diff[i] < 0) {
            s[i] = t[i];
            ans.push_back(s);
        }
    }
    for (int i = s.size() - 1; i >= 0; i--) {
        if (diff[i] > 0) {
            s[i] = t[i];
            ans.push_back(s);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
}
