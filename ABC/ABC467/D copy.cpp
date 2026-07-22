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

int pow2(int n) {
    return n * n;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int px, py, qx, qy, rx, ry, sx, sy;
        cin >> px >> py >> qx >> qy >> rx >> ry >> sx >> sy;
        // int a_kata = (qy - py) / (qx - px);
        // int b_kata = (ry - sy) / (rx - sx);
        pair<int, int> p = {px, py}, q = {qx, qy}, r = {rx, ry}, s = {sx, sy};
        if (px > qx) {
            swap(p, q);
        }
        if (rx > sx) {
            swap(r, s);
        }
        bool same = ((p == r) && (q == s));
        int alength = pow2(p.first - q.first) + pow2(p.second - q.second);
        int blength = pow2(r.first - s.first) + pow2(r.second - s.second);
        if (!same && alength == blength && (((q.second - p.second) * (r.first - s.first)) == ((r.second - s.second) * (q.first - p.first)))) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
}
