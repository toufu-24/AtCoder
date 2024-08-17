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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> a2(2 * n);
    for (int i = 0; i < n; i++) {
        a2[i] = a[i];
        a2[i + n] = a[i];
    }
    vector<int> sum(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        sum[i + 1] = sum[i] + a2[i];
    }
    vector<int> mod(2 * n + 1);
    for (int i = 0; i <= 2 * n; i++) {
        mod[i] = sum[i] % m;
    }

    vector<int> cnt(m, 0);
    int ans = 0;
    // j = i+1 ~ i+n-1 までで mod[i] == mod[j] となるものの数を数える
    int before_n = 0;
    for (int i = 0; i < 2 * n; i++) {
        ans += cnt[mod[i]];
        // mod cnt の処理
        cnt[mod[i]]++;
        if (i >= n - 1) {
            cnt[mod[i - n + 1]]--;
        }
        if (i == n - 1) {
            before_n = ans;
        }
    }
    ans -= before_n;
    cout << ans << endl;
}
