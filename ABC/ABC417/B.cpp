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
    multiset<int> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s.insert(a[i]);
    }

    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        if (s.contains(b[i])) {
            s.erase(s.find(b[i]));
        }
    }

    for (auto x : s) {
        cout << x << " ";
    }
    cout << endl;
}
