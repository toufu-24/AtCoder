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
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<int> point(n, 0);
    vector<int> sum(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '1') {
                sum[j]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (sum[j] > n / 2 && s[i][j] == '0') {
                point[i]++;
            } else if (sum[j] <= n / 2 && s[i][j] == '1') {
                point[i]++;
            }
        }
    }

    int max_point = *max_element(all(point));
    for (int i = 0; i < n; i++) {
        if (point[i] == max_point) {
            cout << i + 1 << " ";
        }
    }
}
