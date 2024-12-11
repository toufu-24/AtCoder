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
    vector<string> s(n);
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
    }
    string X;
    cin >> X;

    int ans = 0;
    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (s[i] == X) {
            flag = true;
        } else if (flag) {
            ans += t[i];
        }
    }
    cout << ans << endl;
}
