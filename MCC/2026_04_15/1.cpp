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
    string t;
    for (int i = 0; i < 1e5; i++) {
        t.push_back('o');
        t.push_back('x');
        t.push_back('x');
    }

    for (int i = 0; i < t.size(); i++) {
        int j = i + s.size() - 1;
        if (j >= t.size()) {
            break;
        }

        string tmp;
        for (int k = i; k <= j; k++) {
            tmp.push_back(t[k]);
        }

        if (tmp == s) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
