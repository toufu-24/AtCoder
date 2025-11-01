# pragma GCC optimize("O3")
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
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    multiset<int> left, right;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (left.size() < k) {
            left.insert(a[i]);
        } else {
            if (*left.rbegin() > a[i]) {
                right.insert(*left.rbegin());
                left.erase(left.find(*left.rbegin()));
                left.insert(a[i]);
            } else {
                right.insert(a[i]);
            }
        }
    }
    right.insert(1e18);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            if (left.size() < k) {
                left.insert(x);
            } else {
                if (*left.rbegin() > x) {
                    right.insert(*left.rbegin());
                    left.erase(left.find(*left.rbegin()));
                    left.insert(x);
                } else {
                    right.insert(x);
                }
            }
        }
        else if (op == 2) {
            int y;
            cin >> y;
            int max_left = *left.rbegin();
            int next_max_left = max_left + y;
            if (next_max_left > *right.begin()) {
                left.erase(left.find(*left.rbegin()));
                left.insert(*right.begin());
                right.erase(right.find(*right.begin()));
                right.insert(next_max_left);
            } else {
                left.erase(left.find(*left.rbegin()));
                left.insert(next_max_left);
            }
        }
        else if (op == 3) {
            cout << *left.rbegin() << '\n';
        }
    }
}