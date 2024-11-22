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

    vector<int> idx;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '/') {
            idx.push_back(i);
        }
    }
    int ans = 0;
    for (int i = 0; i < idx.size(); i++) {
        int slash = idx[i];
        int l = idx[i] - 1;
        int r = idx[i] + 1;
        while (l >= 0 && s[l] == '1' && r < s.size() && s[r] == '2') {
            l--;
            r++;
        }
        ans = max(ans, r - l - 1);
    }
    cout << ans << endl;
}
