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
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        if (n % 2 == 0) {
            if (i % 2 == 0) {
                dq.push_back(a[i]);
            } else {
                dq.push_front(a[i]);
            }
        } else {
            if (i % 2 != 0) {
                dq.push_back(a[i]);
            } else {
                dq.push_front(a[i]);
            }
        }
    }

    for (auto x : dq) {
        cout << x << " ";
    }
}
