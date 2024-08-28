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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    SORT(s);
    do {
        bool ans = true;
        for (int i = 0; i < n - 1; i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                cnt += s[i][j] != s[i + 1][j];
            }
            if (cnt > 1) {
                ans = false;
                break;
            }
        }
        if (ans) {
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(all(s)));
    cout << "No" << endl;
}
