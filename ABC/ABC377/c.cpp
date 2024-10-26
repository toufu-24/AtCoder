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
    vector<int> a(m), b(m);
    set<pair<int, int>> no;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        no.insert({a[i], b[i]});
    }
    vector<int> comb = {1, 2};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            int na = a[i], nb = b[i];
            na += comb[j == 0];
            nb += comb[j == 1];
            if (na <= n && nb <= n) {
                no.insert({na, nb});
            }
            na = a[i], nb = b[i];
            na -= comb[j == 0];
            nb -= comb[j == 1];
            if (na >= 1 && nb >= 1) {
                no.insert({na, nb});
            }
            na = a[i], nb = b[i];
            na += comb[j == 0];
            nb -= comb[j == 1];
            if (na <= n && nb >= 1) {
                no.insert({na, nb});
            }
            na = a[i], nb = b[i];
            na -= comb[j == 0];
            nb += comb[j == 1];
            if (na >= 1 && nb <= n) {
                no.insert({na, nb});
            }
        }
    }

    int ans = n * n;
    ans -= no.size();
    cout << ans << endl;
}
