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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    SORT(A);
    vector<int> sum(N + 1, 0);
    for (int i = 0; i < N; i++) {
        sum[i + 1] = sum[i] + A[i];
    }

    modint::set_mod(100000000);
    int mod = 100000000;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int over_idx = lower_bound(all(A), mod - A[i]) - A.begin();
        if (over_idx <= i) {
            over_idx++;
        }
        ans += A[i] * (N - 1);
        ans -= mod / 2 * (N - over_idx);
    }
    cout << ans << endl;
}
