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
    int cnt = 0;
    for (int now = 0; true; now++) {
        vector<int> two_now;
        int tmp = now;
        while (tmp != 0) {
            two_now.push_back(tmp % 2);
            tmp /= 2;
        }
        REVERSE(two_now);
        string ans;
        for (int i = 0; i < n; i++) {
            ans += 'A';
        }
        for (int i = 0; i < two_now.size(); i++) {
            ans[n - two_now.size() + i] = two_now[i] == 1 ? 'M' : 'A';
        }
        bool mma = false;
        string s = ans.substr(0, 3);
        // cerr << ans << endl;
        if (s == "MMA") {
            mma = true;
            // break;
        }
        for (int i = 3; i < n; i++) {
            s = s.substr(1) + ans[i];
            if (s == "MMA") {
                mma = true;
                break;
            }
        }
        if (mma) {
            cnt++;
            // cerr << ans << endl;
            if (cnt == k) {
                cout << ans << endl;
                return 0;
            }
        }
    }
}