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
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    string ans = "";
    for (int i = 0; i < n; i++) {
        if (s[i][0] >= 's') {
            s[i][0]--;
        }
        if (s[i][0] >= 'y') {
            s[i][0]--;
        }
        ans += (s[i][0] - 'a') / 3 + 2 + '0';
    }
    cout << ans << endl;
}
