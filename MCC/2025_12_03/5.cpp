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

int mypow(int n) {
    int ret = 1;
    for (int i = 0; i < n; i++) {
        ret *= 10;
    }
    return ret;
}

int32_t main() {
    int k;
    cin >> k;
    string s, t;
    cin >> s >> t;
    vector<int> remain(10, k);
    remain[0] = 0;
    int sum = 9 * k - 8;
    vector<int> shand(10, 0), thand(10, 0);
    for (int i = 0; i < 4; i++) {
        shand[s[i] - '0']++;
        thand[t[i] - '0']++;
        remain[s[i] - '0']--;
        remain[s[i] - '0']--;
    }
    int win = 0;
    int total = 0;
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            int sscore = 0, tscore = 0;
            bool ok = true;
            if (remain[i] >= 1 && remain[j] >= 1) {
                if (i == j) {
                    if (remain[i] < 2) {
                        ok = false;
                    }
                }
                if (ok) {
                    shand[i]++;
                    thand[j]++;
                    for (int k = 1; k <= 9; k++) {
                        sscore += k * mypow(shand[k]);
                        tscore += k * mypow(thand[k]);
                    }
                    if (sscore > tscore) {
                        win++;
                    }
                    total++;
                    shand[i]--;
                    thand[j]--;
                }
            }
        }
    }
    cout << fixed << setprecision(10);
    cout << (ld)(win) / total << endl;
}
