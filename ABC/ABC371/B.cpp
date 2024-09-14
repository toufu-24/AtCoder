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
    vector<int> a(m);
    vector<char> b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }
    vector<int> ans(m);
    set<int> exist;
    for (int i = 0; i < m; i++) {
        if (b[i] == 'M' && !exist.contains(a[i])) {
            cout << "Yes" << endl;
            exist.insert(a[i]);
        } else {
            cout << "No" << endl;
        }
    }
}
