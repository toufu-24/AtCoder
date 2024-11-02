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
    vector<pair<int, int>> qr(n);
    for (int i = 0; i < n; i++) {
        cin >> qr[i].first >> qr[i].second;
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int t, d;
        cin >> t >> d;
        t--;
        int q = qr[t].first, r = qr[t].second;
        d = (d < r) ? r : d;
        d += (q - (d - r) % q) % q; 
        cout << d << endl;
    }
}
