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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> pq;
    pq.push_back(0);
    pq.push_back(360);
    int now_degree = 0;
    for (int i = 0; i < n; i++) {
        now_degree += a[i];
        now_degree %= 360;
        pq.push_back(now_degree);
    }
    SORT(pq);
    int ans = 0;
    for (int i = 0; i < pq.size() - 1; i++) {
        ans = max(ans, pq[i + 1] - pq[i]);
    }
    cout << ans << endl;
}
