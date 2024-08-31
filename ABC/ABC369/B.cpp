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
    vector<int> a(n);
    vector<char> s(n);
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> s[i];
        if (s[i] == 'L' && left == 0) {
            left = a[i];
        } else if (s[i] == 'R' && right == 0) {
            right = a[i];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
        case 'L': {
            ans += abs(left - a[i]);
            left = a[i];
            break;
        }
        case 'R': {
            ans += abs(right - a[i]);
            right = a[i];
            break;
        }
        }
    }
    cout << ans << endl;
}
