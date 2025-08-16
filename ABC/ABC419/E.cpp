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
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n <= l) {
        int sum = reduce(all(a));
        sum %= m;
        cout << (m - sum) % m << endl;
    }

    vector<vector<int>> eikyo(n - l + 1);
    for (int i = 0; i < eikyo.size(); i++) {
        for (int j = 0; j < l; j++) {
            assert(i + j < n);
            eikyo[i].push_back(i + j);
        }
    }
    vector<int> eikyo_sum(n - l + 1, 0);
    for (int i = 0; i < n - l + 1; i++) {
        for (int j = 0; j < eikyo[i].size(); j++) {
            eikyo_sum[i] += a[eikyo[i][j]];
            eikyo_sum[i] %= m;
        }
    }

    // Lで影響するが，-L~Lまでどこか選べる
}
