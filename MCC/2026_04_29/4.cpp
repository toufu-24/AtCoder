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
    string s;
    cin >> s;
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i < n; i++) {
        // string ac = to_string(s[i - 1]) + to_string(s[i]);
        char tmp[] = {s[i - 1], s[i], '\0'};
        string ac = string(tmp);
        cnt[i + 1] = cnt[i] + (ac == "AC");
        // cerr << ac << endl;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        // l--;
        cout << cnt[r] - cnt[l] << endl;
    }
}
