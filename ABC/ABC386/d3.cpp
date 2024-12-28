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
        if (get<1>(a) == get<1>(b)) {
            if (get<2>(a) == 'B') {
                return true;
            }
            return false;
        }
        return get<1>(a) > get<1>(b);
    });
    bool ans = true;
    set<int> black;
    for (int i = 0; i < m; i++) {
        if (get<2>(v[i]) == 'B') {
            black.insert(get<0>(v[i]));
        } else {
            auto itr = black.lower_bound(get<0>(v[i]));
            if (itr != black.end()) {
                ans = false;
                break;
            }
        }
    }
    cout << (ans ? "Yes" : "No") << endl;
}
