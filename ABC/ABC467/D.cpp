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

struct point {
    int x, y;
};

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
        point p = {px, py}, q = {qx, qy}, r = {rx, ry}, s = {sx, sy};
        if (px > qx) {
            swap(p, q);
        }
        if (rx > sx) {
            swap(r, s);
        }

        // 垂直二等分線が交わればYes
        // 平行でない -> Yes
        // 垂直二等分線の傾きは-1倍
        // 平行だけど切片が同じ -> Yes
        // 中点の差がaで行ける？
        // それ以外 -> No

        bool isheikou = ((q.y - p.y) * (r.x - s.x)) == ((r.y - s.y) * (q.x - p.x));
        using a_kata = ratio<(q.y - p.y), (q.x - p.x)>;
    }
}
