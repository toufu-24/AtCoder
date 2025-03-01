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

struct UnionFind {
    vector<int> data;
    vector<int> su;

    UnionFind(int sz) {
        data.assign(sz, -1);
        su.resize(sz);
        iota(all(su), 0);
    }

    bool unite(int x, int y, int s) {
        x = find(x), y = find(y);
        if (x == y)
            return (false);
        if (data[x] > data[y])
            swap(x, y);
        data[x] += data[y];
        data[y] = x;
        su[y] = s;
        su[x] = s;
        return true;
    }

    int find(int k) {
        if (data[k] < 0)
            return k;
        return find(data[k]);
    }

    int size(int k) {
        return -data[find(k)];
    }
};

int32_t main() {
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            uf.unite(a, b, uf.su[uf.find(b)]);
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            swap(uf.su[uf.find(a)], uf.su[uf.find(b)]);
        } else if (t == 3) {
            int a;
            cin >> a;
            a--;
            cout << uf.su[uf.find(a)] + 1 << endl;
        }
    }
}