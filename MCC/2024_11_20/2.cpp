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
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }
    int ori_n = n;
    a.push_back(t), b.push_back(t);
    a.insert(a.begin(), 0), b.insert(b.begin(), 0);

    bool ng = false;
    for (int i = 0; i < a.size() - 1; i++) {
        n -= a[i + 1] - b[i];
        if (n <= 0) {
            ng = true;
            break;
        }
        n = min(n + b[i + 1] - a[i + 1], ori_n);
    }
    if (n < 0) {
        ng = true;
    }
    if (ng) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
    }
}