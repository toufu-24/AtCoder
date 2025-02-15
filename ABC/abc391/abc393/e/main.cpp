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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    const int max_a = 1300000;
    vector<int> tmp(max_a, 0);
    for (auto x : a) {
        tmp[x]++;
    }

    // iの倍数の個数
    vector<int> cnt(max_a, 0);
    for (int i = 1; i <= max_a; i++) {
        for (int j = i; j <= max_a; j += i) {
            cnt[i] += tmp[j];
        }
    }
    vector<bool> valid(max_a, false);
    for (int i = 1; i <= max_a; i++) {
        if (cnt[i] >= k) {
            valid[i] = true;
        }
    }
    vector<int> ans(max_a, 0);
    for (int i = 1; i <= max_a; i++) {
        if (valid[i]) {
            for (int j = i; j <= max_a; j += i) {
                ans[j] = max(ans[j], i);
            }
        }
    }

    for (auto x : a) {
        cout << ans[x] << '\n';
    }
}