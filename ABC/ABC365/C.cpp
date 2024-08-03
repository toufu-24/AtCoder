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
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int sum = reduce(all(A));
    if (sum <= M) {
        cout << "infinite" << endl;
        return 0;
    }

    int ok = 0, ng = 1e18;
    while (ng - ok > 1) {
        // x
        int mid = (ok + ng) / 2;
        int sum = 0;
        for (int i = 0; i < N; i++) {
            sum += min(A[i], mid);
        }
        if (sum <= M) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    cout << ok << endl;
}
