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
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int ans = 1e18;
    for (int i = 0; i < n; i++) {
        int tmp_ans = a * i;
        string tmp =  s.substr(i) + s.substr(0, i);
        // cerr << s.substr(0, i) << " " << s.substr(i) << endl;
        // cerr << tmp << endl;
        int left = 0, right = n - 1;
        while (left < right) {
            if (tmp[left] != tmp[right]) {
                tmp_ans += b;
                // cerr << left << " " << right << endl;
            }
            left++, right--;
        }
        // cerr << tmp_ans << endl;
        ans = min(ans, tmp_ans);
    }
    cout << ans << endl;
}
