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
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < n; i++) {
        int ans = s[i].size();
        for (int j = 0; j < i; j++) {
            int tmp = 0;
            int prefix_cnt = 0;
            for (int k = 0; k < s[j].size(); k++) {
                if (s[i].size() <= k) {
                    break;
                }
                if (s[j][k] == s[i][k]) {
                    prefix_cnt++;
                } else {
                    break;
                }
            }
            tmp = s[j].size() + s[i].size() - 2 * prefix_cnt;
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }
}