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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int now = 0;
    int right = 0;
    while (true) {
        if (now >= n) {
            break;
        }
        if (now <= right) {
            right = max(right, now + a[now] - 1);
        } else {
            break;
        }
        now++;
    }
    cout << now << endl;
}
