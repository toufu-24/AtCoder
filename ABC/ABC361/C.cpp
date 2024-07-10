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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    SORT(A);
    int ans = 1e18;

    for (int i = 0; i < N; i++) {
        if (i + N - K - 1 >= N) {
            break;
        }
        int now = A[i + N - K - 1] - A[i];
        ans = min(ans, now);
    }

    cout << ans << endl;
}
