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
    vector<int> X(m), Y(m);
    vector<char> C(m);
    vector<tuple<int, int, char>> v;
    for (int i = 0; i < m; i++) {
        cin >> X[i] >> Y[i] >> C[i];
        v.push_back({X[i], Y[i], C[i]});
    }
    sort(all(v), [](auto a, auto b) {
        return get<0>(a) < get<0>(b);
    });
    char ini = 'B';
    bool ans = true;
    bool changed = false;
    for (int i = 0; i < m; i++) {
        if (get<2>(v[i]) != ini) {
            if (changed) {
                // ans = false;
                break;
            }
            ini = get<2>(v[i]);
            changed = true;
        }
    }

    sort(all(v), [](auto a, auto b) {
        return get<1>(a) < get<1>(b);
    });
    ini = 'B';
    changed = false;
    for (int i = 0; i < m; i++) {
        if (get<2>(v[i]) != ini) {
            if (changed) {
                ans = false;
                break;
            }
            ini = get<2>(v[i]);
            changed = true;
        }
    }
    cout << (ans ? "Yes" : "No") << endl;
}
