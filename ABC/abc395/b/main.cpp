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
    string tmp = "";
    for (int j = 0; j < n; j++) {
        tmp += "a";
    }
    vector<string> ans(n, tmp);
    for (int i = 0; i < n; i++) {
        int j = n - i;
        if (i > j) {
            continue;
        }
        char ch;
        if (i % 2 == 0) {
            ch = '#';
        } else {
            ch = '.';
        }

        for (int ii = i; ii < j; ii++) {
            for (int jj = i; jj < j; jj++) {
                ans[ii][jj] = ch;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}
