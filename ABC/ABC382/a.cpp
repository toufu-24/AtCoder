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
    int n, d;
    cin >> n >> d;
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '@') {
            cnt++;
        }
    }
    int ans = n - cnt;
    cout << ans + d << endl;
}
