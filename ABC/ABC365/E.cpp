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

    int ans = 0;
    for (int bit = 0; bit < 32; bit++) {
        int tmp = 0;
        vector<int> xorsum(N + 1, 0);
        for (int i = 0; i < N; i++) {
            xorsum[i + 1] = xorsum[i] ^ ((A[i] >> bit) & 1);
        }

        vector<int> cnt(2, 0);
        for (int i = 0; i <= N; i++) {
            cnt[xorsum[i]]++;
        }

        ans += cnt[0] * cnt[1] * (1LL << bit);
    }
    cerr << ans << endl;

    // 区間1を省く
    for (int i = 0; i < N; i++) {
        ans -= A[i];
    }

    cout << ans << endl;
}
