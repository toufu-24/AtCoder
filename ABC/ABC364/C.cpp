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
    int N, X, Y;
    cin >> N >> X >> Y;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    RSORT(A), RSORT(B);
    int ans = N;
    int a_sum = 0, b_sum = 0;
    for (int i = 0; i < N; i++) {
        a_sum += A[i];
        b_sum += B[i];
        if (a_sum > X || b_sum > Y) {
            ans = min(ans, i + 1);
            break;
        }
    }
    cout << ans << endl;
}
