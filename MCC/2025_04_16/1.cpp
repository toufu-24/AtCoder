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
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '/') {
            int left = i - 1, right = i + 1;
            while (left >= 0 && s[left] == '1') {
                left--;
            }
            while (right < n && s[right] == '2') {
                right++;
            }
            int dist = min(right - i, i - left);
            ans = max(ans, dist * 2 - 1);
        }
    }
    cout << ans << endl;
}