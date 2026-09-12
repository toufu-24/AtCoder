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
    int n, m, k;
    cin >> n >> m >> k;
    string t;
    cin >> t;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        // cin >> s[i];
        string tmp;
        cin >> tmp;
        s[i].resize(k);
        for (int j = 0; j < k; j++) {
            if (tmp[j] == t[j]) {
                s[i][j] = 'o';
            } else {
                s[i][j] = 'x';
            }
        }
    }
    vector<int> pass(k + 1, 0);
    vector<int> passed(n, k);
    int cnt = n;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (s[j][i] == 'o' && passed[j] == k) {
                pass[i]++;
                passed[j] = i;
                cnt--;
            }
        }
    }
    pass[k] = cnt;

    int q;
    cin >> q;
    while (q--) {
        int i, j;
        cin >> i >> j;
        i--, j--;
        s[i][j] = (s[i][j] == 'o') ? 'x' : 'o';
        // if (s[i][j] == 'o') {
        //     if (passed[i] < j) {
        //     } else {
        //         pass[passed[i]]--;
        //         pass[j]++;
        //         passed[i] = j;
        //     }
        // } else {
        //     // x に変わった
        //     if (passed[i] == j) {
        //         pass[j]--;
        //         for (int jj = 0; jj < k; jj++) {
        //             if (s[i][jj] == 'o') {
        //                 passed[i] = jj;
        //                 pass[jj]++;
        //                 assert(j < jj);
        //                 break;
        //             }
        //         }
        //     } else {
        //     }
        // }
        pass[passed[i]]--;

        bool ok = false;
        for (int jj = 0; jj < k; jj++) {
            if (s[i][jj] == 'o') {
                passed[i] = jj;
                pass[jj]++;
                ok = true;

                break;
            }
        }
        if (!ok) {
            passed[i] = k;
            pass[k]++;
        }
        int sum = 0;
        int idx = k + 2;
        for (int jj = 0; jj <= k; jj++) {
            sum += pass[jj];
            if (sum > m) {
                idx = jj - 1;
                break;
            }
        }

        if (passed[i] <= idx) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
