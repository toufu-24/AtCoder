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
    vector<vector<pair<int, int>>> shougen(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int j = 0; j < a; j++) {
            int x, y;
            cin >> x >> y;
            x--;
            shougen[i].push_back({x, y});
        }
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool flag = true;
        // -1 -> 未定, 0-> 嘘つき, 1-> 正直者
        vector<int> sinngi(n, -1);
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (sinngi[i] == -1) {
                    sinngi[i] = 1;
                } else if (sinngi[i] == 0) {
                    flag = false;
                }
                for (auto [x, y] : shougen[i]) {
                    if (sinngi[x] == -1) {
                        sinngi[x] = y;
                    } else if (sinngi[x] != y) {
                        flag = false;
                    }
                }
            } else {
                if (sinngi[i] == -1) {
                    sinngi[i] = 0;
                } else if (sinngi[i] == 1) {
                    flag = false;
                }
            }
        }
        if (flag) {
            ans = max<int>(ans, __builtin_popcount(mask));
        }
    }
    cout << ans << endl;
}
