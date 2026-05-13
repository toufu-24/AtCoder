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
    vector<int> two(n, 0);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int cnt = 0;
        while (a[i] % 2 == 0) {
            cnt++;
            a[i] /= 2;
        }
        two[i] = cnt;
    }

    SORT(two);
    // 0404040
    // 0404222
    map<int, int> cnt;
    for (auto x : two) {
        if (x >= 2) {
            cnt[4]++;
        } else if (x >= 1) {
            cnt[2]++;
        } else {
            cnt[0]++;
        }
    }

    bool ans = false;
    if (cnt[2] == 0 && (cnt[0] - 1 <= cnt[4])) {
        ans = true;
    }
    if (cnt[0] <= cnt[4]) {
        ans = true;
    }

    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
