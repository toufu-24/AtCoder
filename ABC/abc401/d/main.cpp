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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    // o の隣は . である
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') {
            if (i - 1 >= 0) {
                s[i - 1] = '.';
            }
            if (i + 1 < n) {
                s[i + 1] = '.';
            }
        }
    }
    string ans = s;
    int o_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') {
            o_cnt++;
        }
    }
    k -= o_cnt;
    // 連続する?が確定しているならそうする
    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (s[i] != '?') {
            continue;
        }
        int left = i;
        int right = i + 1;
        while (right < n && ans[right] == '?') {
            right++;
        }
        // [left, right) は全て?
        int len = right - left;
        if (len % 2 == 1) {
            for (int j = left; j < right; j++) {
                if ((j - left) % 2 == 0) {
                    ans[j] = 'o';
                    k--;
                } else {
                    ans[j] = '.';
                }
            }
        }
        i = right - 1;
    }
    if(k != 0){
        ans = s;
    }
    cout << ans << endl;
}
