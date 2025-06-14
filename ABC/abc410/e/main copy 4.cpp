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
        if (a_acc[a_taosu] > h) {
            break;
        }
        // vector<int> b_taosu_list;
        vector<pair<int, int>> b_taosu_list;
        for (int b_taosu = a_taosu; b_taosu < n; b_taosu++) {
            b_taosu_list.push_back({get<1>(ab[b_taosu]), b_taosu});
        }
        SORT(b_taosu_list);
        for (int i = 0; i < b_taosu_list.size(); i++) {
            if (b_acc[b_taosu_list[i].second + 1] - b_acc[a_taosu] > m) {
                break;
            }
            ans = max(ans, a_taosu + i + 1);
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
        if (b_acc[b_taosu] > m) {
            break;
        }
        vector<pair<int, int>> a_taosu_list;
        for (int a_taosu = b_taosu; a_taosu < n; a_taosu++) {
            a_taosu_list.push_back({get<1>(ab[a_taosu]), a_taosu});
        }
        SORT(a_taosu_list);
        for (int i = 0; i < a_taosu_list.size(); i++) {
            if (a_acc[a_taosu_list[i].second + 1] - a_acc[b_taosu] > h) {
                break;
            }
            ans = max(ans, b_taosu + i + 1);
        }
    }
    cout << ans << endl;
}
