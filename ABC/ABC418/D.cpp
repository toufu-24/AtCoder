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
    // 0の個数が偶数個であるような区間の数の数え上げ
    vector<int> parity(n + 1, 0);
    for (int i = 0; i < n; i++) {
        parity[i + 1] = parity[i] ^ (s[i] == '0');
    }
    map<int, int> cnt;
    cnt[0] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += cnt[parity[i]];
        cnt[parity[i]]++;
    }
    cout << ans << endl;
}
