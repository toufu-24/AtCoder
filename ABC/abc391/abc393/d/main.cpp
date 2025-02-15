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

    vector<int> kosuu(n + 1, 0);
    for (int i = 1; i < n; i++) {
        if (s[i] == '1') {
            kosuu[i] = kosuu[i - 1] + 1;
        } else {
            kosuu[i] = kosuu[i - 1];
        }
    }
    // 1が少ない方に移動させる
    int ans = 0;
    int left = s.find('1');
    int right = s.rfind('1');
    for (int i = 0; i < n; i++) {
        if (i < left || i > right) {
            continue;
        }
        if (s[i] == '0') {
            if (i - kosuu[i] < n - i - (kosuu[n] - kosuu[i])) {
                ans += i - left;
                s[i] = '1';
                s[left] = '0';
                left++;
            } else {
                ans += right - i;
                s[i] = '1';
                s[right] = '0';
                right--;
            }
        }
        if (n - 1 - i < left || n - 1 - i > right) {
            continue;
        }
        if (s[n - 1 - i] == '0') {
            if (i - kosuu[n - 1 - i] < n - i - (kosuu[n] - kosuu[n - 1 - i])) {
                ans += right - (n - 1 - i);
                s[n - 1 - i] = '1';
                s[right] = '0';
                right--;
            } else {
                ans += i - left;
                s[n - 1 - i] = '1';
                s[left] = '0';
                left++;
            }
        }
        if (i >= n - 1 - i) {
            break;
        }
    }
    cout << ans << endl;
}
