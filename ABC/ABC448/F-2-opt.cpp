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
    double start = clock();
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    vector<int> ans(n);
    iota(all(ans), 0);
    while ((clock() - start) < 1.9 * CLOCKS_PER_SEC) {
        int a = rand() % (n - 1);
        int b = rand() % (n - 1);
        if (a > b) {
            swap(a, b);
        }

        int now_cost = abs(x[a] - x[a + 1]) + abs(y[a] - y[a + 1]) + abs(x[b] - x[b + 1]) + abs(y[b] - y[b + 1]);
        int next_cost = abs(x[a] - x[b + 1]) + abs(y[a] - y[b + 1]) + abs(x[b] - x[a + 1]) + abs(y[b] - y[a + 1]);

        if (now_cost > next_cost) {
            a++;
            while (a < b) {
                swap(ans[a++], ans[b--]);
            }
        }
    }

    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
