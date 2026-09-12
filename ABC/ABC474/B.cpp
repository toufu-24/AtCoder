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
    vector<int> otu(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        otu[i] = 1000 - a[i] % 1000;
        if (otu[i] == 1000) {
            otu[i] = 0;
        }
    }

    int hy = 0, ju = 0, it = 0;
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        string o = to_string(otu[i]);
        while (o.size() <= 2) {
            o = '0' + o;
        }
        assert(o.size() == 3);
        hy += (o[0] - '0');
        ju += (o[1] - '0');
        it += (o[2] - '0');
    }

    cout << it << " " << ju << " " << hy << endl;
}
