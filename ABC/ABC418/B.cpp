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
    ld ans = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            string now = s.substr(i, j - i + 1);
            if (now.back() != 't' || now.front() != 't') {
                ans = max(ans, 0.0L);
            }
            int cnt = 0;
            for (int k = 0; k < now.size(); k++) {
                if (now[k] == 't') {
                    cnt++;
                }
            }
            ans = max(ans, (ld)(cnt - 2) / (ld)(now.size() - 2));
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
