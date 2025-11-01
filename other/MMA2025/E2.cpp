#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;
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
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pq.size() < k) {
            pq.push(a[i]);
        } else {
            if (pq.top() > a[i]) {
                pq.pop();
                pq.push(a[i]);
            }
        }
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            if (pq.size() < k) {
                pq.push(x);
            } else {
                if (pq.top() > x) {
                    pq.pop();
                    pq.push(x);
                }
            }
        }
        if (op == 2) {
            int y;
            cin >> y;
            int top = pq.top();
            pq.pop();
            pq.push(top + y);
        }
        if (op == 3) {
            cout << pq.top() << endl;
        }
    }
}