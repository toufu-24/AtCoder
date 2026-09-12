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
    int n, s, l;
    cin >> n >> s >> l;
    s--;
    vector<int> a(n - 1);
    vector<int> sum(n, 0);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        sum[i + 1] = sum[i] + a[i];
    }

    int ans = 0;
    for (int i = 0; i <= s; i++) {
        for (int j = max(i, s); j < n; j++) {
            int le = sum[s] - sum[i];
            int ri = sum[j] - sum[s];
            int va = min(le + ri * 2, le * 2 + ri);
            if (va <= l) {
                ans = max(ans, (j - i + 1));
            }
        }
    }
    cout << ans << endl;
}
