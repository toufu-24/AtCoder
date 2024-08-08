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
    vector<int> B(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> B[i];
    }
    vector<int> A(N);
    A[0] = B[0];
    for (int i = 1; i < N - 1; i++) {
        A[i] = min(B[i], B[i - 1]);
    }
    A[N - 1] = B[N - 2];
    int ans = reduce(all(A));
    cout << ans << endl;
}
