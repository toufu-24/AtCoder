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
    RSORT(a);
    vector<int> b(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> b[i];
    }
    RSORT(b);

    vector<int> not_in;
    priority_queue<int> a_pq, b_pq;
    for (int i = 0; i < n; i++) {
        a_pq.push(a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        b_pq.push(b[i]);
    }
    while (!a_pq.empty() && !b_pq.empty()) {
        int b_top = b_pq.top();
        b_pq.pop();
        if (a_pq.top() > b_top) {
            not_in.push_back(a_pq.top());
            b_pq.push(b_top);
        }
        a_pq.pop();
    }
    if (!a_pq.empty()) {
        not_in.push_back(a_pq.top());
    }
    if (not_in.size() != 1) {
        cout << -1 << endl;
        return 0;
    }
    cout << not_in[0] << endl;
}
