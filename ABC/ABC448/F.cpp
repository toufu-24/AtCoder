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

// https://sotanishy.github.io/cp-library-cpp/data-structure/kd_tree.hpp.html
#line 2 "data-structure/kd_tree.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

template <typename T>
class KDTree {
  public:
    void add_point(int id, T x, T y) { points.emplace_back(id, x, y); }

    void build() { build(0, points.size() - 1, 0); }

    std::vector<int> search(T sx, T tx, T sy, T ty) const {
        Point s(std::min(sx, tx), std::min(sy, ty));
        Point t(std::max(sx, tx), std::max(sy, ty));
        std::vector<int> res;
        search(s, t, res, 0, points.size() - 1, 0);
        return res;
    }

  private:
    struct Point {
        int id;
        T x, y;
        Point(T x, T y) : x(x), y(y) {}
        Point(int id, T x, T y) : id(id), x(x), y(y) {}
    };

    std::vector<Point> points;

    int check_position(const Point &p, const Point &s, const Point &t,
                       bool axis) const {
        if (axis == 0) {
            if (p.x < s.x)
                return -1;
            if (t.x < p.x)
                return 1;
            return 0;
        } else {
            if (p.y < s.y)
                return -1;
            if (t.y < p.y)
                return 1;
            return 0;
        }
    }

    void build(int l, int r, bool axis) {
        if (l > r)
            return;
        std::ranges::sort(points.begin() + l, points.begin() + r + 1, {},
                          [&](auto &p) { return axis == 0 ? p.x : p.y; });
        int m = std::midpoint(l, r);
        build(l, m - 1, axis ^ 1);
        build(m + 1, r, axis ^ 1);
    }

    void search(const Point &s, const Point &t, std::vector<int> &res, int l,
                int r, bool axis) const {
        if (l > r)
            return;
        int m = std::midpoint(l, r);
        bool contained = true;
        for (int i = 0; i < 2; i++)
            contained &= check_position(points[m], s, t, i) == 0;
        if (contained)
            res.push_back(points[m].id);
        if (l == r)
            return;
        int pos = check_position(points[m], s, t, axis);
        if (pos != -1)
            search(s, t, res, l, m - 1, axis ^ 1);
        if (pos != 1)
            search(s, t, res, m + 1, r, axis ^ 1);
    }
};
int32_t main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    vector<int> ans(n);
    for (auto x : ans) {
        cout << x + 1 << " ";
    }
}
