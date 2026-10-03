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
    int n, q;
    cin >> n >> q;
    vector<int> l(q), r(q), x(q);
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i] >> x[i];
        l[i]--, r[i]--;
    }
    vector<multiset<int>> imos(n + 1);
    for (int i = 0; i < q; i++) {
        imos[l[i]].insert(x[i]);
        imos[r[i] + 1].insert(-x[i]);
    }

    // multiset<int> now;
    // set<int> st;
    map<int, int> now;
    for (int i = 0; i < n; i++) {
        for (auto x : imos[i]) {
            // 高々2N回しか入らない？
            if (x > 0) {
                // now.insert(x);
                now[x]++;
            } else {
                // now.erase(now.find(-x));
                now[-x]--;
                if (now[-x] == 0) {
                    now.erase(-x);
                }
            }
        }
        cout << now.size() << " ";
    }
}
