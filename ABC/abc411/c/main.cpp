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
    int n, q;
    cin >> n >> q;
    vector<int> a(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i];
        a[i]--;
    }

    if (n == 1) {
        for (int i = 0; i < q; i++) {
            cout << (i + 1) % 2 << endl;
        }
        return 0;
    }

    // false -> siro
    vector<bool> masu(n, false);
    int ans = 0;
    for (int i = 0; i < q; i++) {
        if (a[i] == 0) {
            if (masu[a[i]]) {
                // 右が白なら-1
                if (!masu[a[i] + 1]) {
                    ans--;
                }
            } else {
                // 右が白なら+1
                if (!masu[a[i] + 1]) {
                    ans++;
                }
            }
        } else if (a[i] == n - 1) {
            if (masu[a[i]]) {
                // 左が白なら-1
                if (!masu[a[i] - 1]) {
                    ans--;
                }
            } else {
                // 左が白なら+1
                if (!masu[a[i] - 1]) {
                    ans++;
                }
            }
        } else {
            if (masu[a[i]]) {
                // 隣接がどっちも黒なら+1
                if (masu[a[i] - 1] && masu[a[i] + 1]) {
                    ans++;
                }
                // 隣接がどっちも白なら-1
                else if (!masu[a[i] - 1] && !masu[a[i] + 1]) {
                    ans--;
                }
            } else {
                // 隣接がどっちも黒なら-1
                if (masu[a[i] - 1] && masu[a[i] + 1]) {
                    ans--;
                }
                // 隣接がどっちも白なら+1
                else if (!masu[a[i] - 1] && !masu[a[i] + 1]) {
                    ans++;
                }
            }
        }
        masu[a[i]] = !masu[a[i]];
        cout << ans << endl;
    }
}