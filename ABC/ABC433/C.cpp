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
    int n = s.size();
    int left = 0, right = 0;
    int ans = 0;
    while (true) {
        while (right < n && s[left] == s[right]) {
            right++;
        }
        int mid = right;
        while (right < n && s[left] + 1 == s[right]) {
            right++;
        }
        ans += min(mid - left, right - mid);
        left = mid;
        if (left == n) {
            break;
        }
    }
    cout << ans << endl;
}
