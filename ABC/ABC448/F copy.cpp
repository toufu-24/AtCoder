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

    vector<bool> used(n, false);
    used[0] = true;
    int now = 0;
    cout << 1 << " ";
    for (int i = 0; i < n - 1; i++) {
        int min_dis = 1e9;
        int min_idx = i;
        for (int j = 0; j < n; j++) {
            if (used[j]) {
                continue;
            }
            int tmp = abs(x[i] - x[j]) + abs(y[i] - y[j]);
            min_dis = min(min_dis, tmp);
            if (min_dis == tmp) {
                min_idx = j;
            }
        }
        used[min_idx] = true;
        cout << min_idx + 1 << " ";
    }
}
