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

// https://ei1333.github.io/luzhiled/snippets/other/compress.html
template <typename T>
struct Compress {
    vector<T> xs;

    Compress() = default;

    Compress(const vector<T> &vs) {
        add(vs);
    }

    Compress(const initializer_list<vector<T>> &vs) {
        for (auto &p : vs)
            add(p);
    }

    void add(const vector<T> &vs) {
        copy(begin(vs), end(vs), back_inserter(xs));
    }

    void add(const T &x) {
        xs.emplace_back(x);
    }

    void build() {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
    }

    vector<int> get(const vector<T> &vs) const {
        vector<int> ret;
        transform(begin(vs), end(vs), back_inserter(ret), [&](const T &x) {
            return lower_bound(begin(xs), end(xs), x) - begin(xs);
        });
        return ret;
    }

    int get(const T &x) const {
        return lower_bound(begin(xs), end(xs), x) - begin(xs);
    }

    const T &operator[](int k) const {
        return xs[k];
    }
};

int32_t main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    Compress<int> comp(x);
    comp.build();
    vector<int> y = comp.get(x);
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        arr[y[i]] += p[i];
    }
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + arr[i];
    }
    // cerr << "x" << endl;
    // for (int i = 0; i < n; i++) {
    //     cerr << x[i] << " ";
    // }
    // cerr << endl;
    // cerr << "arr" << endl;
    // for (int i = 0; i < n; i++) {
    //     cerr << arr[i] << " ";
    // }
    // cerr << endl;
    // cerr << "sum" << endl;
    // for (int i = 0; i < n + 1; i++) {
    //     cerr << sum[i] << " ";
    // }
    int q;
    cin >> q;
    cerr << endl;
    while (q--) {
        int l, r;
        cin >> l >> r;
        // 座圧に変換
        l = lower_bound(all(x), l) - x.begin();
        r = upper_bound(all(x), r) - x.begin();
        r--;
        cout << sum[r + 1] - sum[l] << endl;
        // cerr << l << " " << r << endl;
    }
}
