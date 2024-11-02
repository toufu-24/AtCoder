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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    Compress<int> comp(a);
    comp.build();
    for (int i = 0; i < n; i++) {
        a[i] = comp.get(a[i]);
    }

    vector<int> prev(n, -1);
    for (int i = 0; i < n; i++) {
        cout << prev[a[i]] << " ";
        prev[a[i]] = i + 1;
    }
}
