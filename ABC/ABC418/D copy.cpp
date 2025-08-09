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
    string s;
    cin >> s;
    // 0の個数が偶数個であるような区間の数の数え上げ
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string now = s.substr(i, j - i + 1);
            int cnt = 0;
            for (int k = 0; k < now.size(); k++) {
                if (now[k] == '0') {
                    cnt++;
                }
            }
            if (cnt % 2 == 0) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}
