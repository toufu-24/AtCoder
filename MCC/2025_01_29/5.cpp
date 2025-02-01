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
    string s;
    cin >> s;
    if (s.size() <= 2) {
        int num = stoll(s);
        if (num % 8 == 0) {
            cout << "Yes" << endl;
            return 0;
        }
        reverse(all(s));
        num = stoll(s);
        if (num % 8 == 0) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    vector<int> cnt(10, 0);
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - '0']++;
    }
    cnt[0] = 1e9;

    for (int i = 0; i < 1000; i += 8) {
        vector<int> c(10, 0);
        c[i % 10]++;
        c[(i / 10) % 10]++;
        c[(i / 100) % 10]++;
        if (c[0] > 0) {
            continue;
        }
        bool ok = true;
        for (int j = 1; j < 10; j++) {
            if (c[j] > cnt[j]) {
                ok = false;
            }
        }
        if (ok) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
