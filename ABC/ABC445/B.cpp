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
    int m = 0;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        m = max<int>(m, s[i].size());
    }

    for (int i = 0; i < n; i++) {
        int size = m - s[i].size();
        size /= 2;
        for (int j = 0; j < size; j++) {
            cout << '.';
        }
        cout << s[i];
        for (int j = 0; j < size; j++) {
            cout << '.';
        }
        cout << endl;
    }
}
