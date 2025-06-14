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

bool chmax(int &a, int b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

int32_t main() {
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<tuple<int, int, int>> ab(n);
    for (int i = 0; i < n; i++) {
        ab[i] = {a[i], b[i], i};
    }
    SORT(ab);
    vector<int> a_acc(n + 1, 0), b_acc(n + 1, 0);
    for (int i = 0; i < n; i++) {
        a_acc[i + 1] = a_acc[i] + get<0>(ab[i]);
        b_acc[i + 1] = b_acc[i] + get<1>(ab[i]);
    }
    int ans = 0;
    for (int a_taosu = 0; a_taosu <= n; a_taosu++) {
        for (int b_taosu = a_taosu + 1; b_taosu <= n; b_taosu++) {
            if (a_acc[a_taosu] > h) {
                continue;
            }
            if (b_acc[b_taosu] - b_acc[a_taosu] > m) {
                continue;
            }
            ans = max(ans, b_taosu);
        }
    }

    // 逆も
    for (int i = 0; i < n; i++) {
        ab[i] = {b[i], a[i], i};
    }
    SORT(ab);
    for (int i = 0; i < n; i++) {
        a_acc[i + 1] = a_acc[i] + get<1>(ab[i]);
        b_acc[i + 1] = b_acc[i] + get<0>(ab[i]);
    }
    for (int b_taosu = 0; b_taosu <= n; b_taosu++) {
        for (int a_taosu = b_taosu + 1; a_taosu <= n; a_taosu++) {
            if (b_acc[b_taosu] > m) {
                continue;
            }
            if (a_acc[a_taosu] - a_acc[b_taosu] > h) {
                continue;
            }
            ans = max(ans, a_taosu);
        }
    }
    cout << ans << endl;
}
