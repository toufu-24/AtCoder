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
    int n, k, m;
    cin >> n >> k >> m;
    priority_queue<tuple<int, int, int>> pq;
    vector<int> c(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> v[i];
        pq.push({v[i], c[i], i});
    }
    auto pq2 = pq;

    int cnt = 0;
    int ans = 0;
    set<int> cset, idst;
    while (!pq.empty() && cnt < m) {
        auto [vv, cc, idx] = pq.top();
        pq.pop();
        if (cset.contains(cc)) {
            continue;
        }
        cset.insert(cc);
        idst.insert(idx);
        ans += vv;
        cnt++;
        if (cnt == m) {
            break;
        }
    }

    while (!pq2.empty() && cnt < k) {
        auto [vv, cc, idx] = pq2.top();
        pq2.pop();
        if (idst.contains(idx)) {
            continue;
        }
        ans += vv;
        cnt++;
    }
    cout << ans << endl;
}
