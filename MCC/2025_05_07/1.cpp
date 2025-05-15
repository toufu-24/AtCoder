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
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<int> perm(n);
    iota(all(perm), 0);
    ld ans = 0;
    do {
        ld sum = 0;
        for (int i = 0; i < n - 1; i++) {
            sum += hypot(x[perm[i]] - x[perm[i + 1]], y[perm[i]] - y[perm[i + 1]]);
        }
        ans += sum;
    } while (next_permutation(all(perm)));
    int n_factorial = 1;
    for (int i = 1; i <= n; i++) {
        n_factorial *= i;
    }
    cout << fixed << setprecision(10) << ans / n_factorial << endl;
}
