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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }

        int first = s[0];
        int second = s.back();
        s.pop_back();
        s.erase(s.begin());
        SORT(s);
        vector<int> ans;
        ans.push_back(first);
        bool ok = false;
        if (first * 2 >= second) {
            ans.push_back(second);
            ok = true;
        } else {
            while (true) {
                int prev = ans.back();
                auto next = upper_bound(all(s), prev * 2);
                if (next == s.begin()) {
                    break;
                }
                next--;
                if (*next <= prev) {
                    break;
                }
                ans.push_back(*next);
                if (ans.back() * 2 >= second) {
                    ok = true;
                    ans.push_back(second);
                    break;
                }
            }
        }

        if (ok) {
            cout << ans.size() << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
