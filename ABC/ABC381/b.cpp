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
    if (s.size() % 2 == 1) {
        cout << "No" << endl;
        return 0;
    }
    vector<int> cnt(26, 0);
    for (char c : s) {
        cnt[c - 'a']++;
    }
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[2 * i] != s[2 * i + 1]) {
            cout << "No" << endl;
            return 0;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (cnt[c - 'a'] != 2 && cnt[c - 'a'] != 0) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
