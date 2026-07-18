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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> cb(m);
    vector<int> b(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i] >> c[i];
        cb[i] = {c[i], b[i]};
    }
    RSORT(cb);

    priority_queue<int> pq;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < cb[i].second && pq.size() < n; j++) {
            pq.push(cb[i].first);
        }
    }

    SORT(a);
    int idx = 0;
    while (!pq.empty() && idx < n) {
        if (a[idx] > pq.top()) {
            break;
        }
        a[idx++] = pq.top();
        pq.pop();
    }
    for (auto x : a) {
        cout << x << " ";
    }
    cout << endl;
    cout << reduce(all(a)) << endl;
}
