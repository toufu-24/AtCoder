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
    vector<string> s(n), t(m);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> t[i];
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (a + i >= n || b + j >= n) {
                        goto next;
                    }
                    if (s[a + i][b + j] != t[i][j]) {
                        goto next;
                    }
                }
            }
            cout << a + 1 << " " << b + 1 << endl;
            return 0;
        next:;
        }
    }
}
