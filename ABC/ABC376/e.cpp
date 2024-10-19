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
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        vector<pair<int, int>> a_b(n);
        for (int i = 0; i < n; i++) {
            a_b[i] = {a[i], b[i]};
        }
        SORT(a_b);

        priority_queue<int> pq;
        int sum = 0;
        for (int i = 0; i < k; i++) {
            pq.push(a_b[i].second);
            sum += a_b[i].second;
        }

        int ans = sum * a_b[k - 1].first;
        for (int i = k; i < n; i++) {
            if (pq.top() > a_b[i].second) {
                sum -= pq.top();
                pq.pop();
                sum += a_b[i].second;
                pq.push(a_b[i].second);
            }
            ans = min(ans, sum * a_b[i].first);
        }
        cout << ans << endl;
    }
}
