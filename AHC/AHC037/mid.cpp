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
    int _n;
    cin >> _n;
    constexpr int n = 1000;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> a_sorted = a, b_sorted = b;
    int a_mid = 0, b_mid = 0;
    SORT(a_sorted);
    SORT(b_sorted);
    a_mid = a_sorted[n / 2];
    b_mid = b_sorted[n / 2];

    struct ans_data {
        int before_x, before_y;
        int after_x, after_y;
    };
    vector<ans_data> ans;
    ans.push_back({0, 0, a_mid, b_mid});
    for (int i = 0; i < n; i++) {
        ans.push_back({a_mid, b_mid, a[i], b[i]});
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].before_x << " " << ans[i].before_y << " " << ans[i].after_x << " " << ans[i].after_y << endl;
    }
}
