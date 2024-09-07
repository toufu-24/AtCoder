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

using mint = modint998244353;

int32_t main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }
    mint total = mint(2).pow(n - 1);

    // 和が K である連続部分列が存在する分割を数える
    map<int, int> cnt;
    map<int, vector<int>> cnt2;
    mint valid = 0;
    cnt[0] = 1;
    for (int i = 1; i <= n; i++) {
        int tmp = sum[i] - k;
        if (cnt.contains(tmp)) {
            valid += cnt[tmp] * mint(2).pow(n - i);
        }
        cnt[sum[i]]++;
    }

    mint ans = total - valid;
    cout << ans.val() << endl;
}