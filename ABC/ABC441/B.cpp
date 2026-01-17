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
    string s, t;
    cin >> s >> t;
    set<char> sst, tst;
    for (int i = 0; i < s.size(); i++) {
        sst.insert(s[i]);
    }
    for (int i = 0; i < t.size(); i++) {
        tst.insert(t[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        string w;
        cin >> w;
        bool taka = true, aoki = true;
        for (auto c : w) {
            if (!sst.contains(c)) {
                taka = false;
            }
            if (!tst.contains(c)) {
                aoki = false;
            }
        }

        if (taka && aoki) {
            cout << "Unknown" << endl;
        } else if (taka) {
            cout << "Takahashi" << endl;
        } else if (aoki) {
            cout << "Aoki" << endl;
        } else {
            cout << "Unknown" << endl;
        }
    }
}
