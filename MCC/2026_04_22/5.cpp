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

    int left = 0, right = 0;
    set<int> now;
    int ans = 0;
    while (true) {
        if (right + 1 >= n) {
            break;
        }
        while (a[right] == a[right + 1] && !now.contains(a[right])) {
            now.insert(a[right]);
            right += 2;
            if (right + 1 >= n) {
                break;
            }
        }
        ans = max(ans, right - left);
        if (now.contains(a[left])) {
            now.erase(a[left]);
        }
        left += 2;
        right = max(right, left);
    }

    now.clear();
    left = 1, right = 1;
    while (true) {
        if (right + 1 >= n) {
            break;
        }
        while (a[right] == a[right + 1] && !now.contains(a[right])) {
            now.insert(a[right]);
            right += 2;
            if (right + 1 >= n) {
                break;
            }
        }
        ans = max(ans, right - left);
        if (now.contains(a[left])) {
            now.erase(a[left]);
        }
        left += 2;
        right = max(right, left);
    }
    cout << ans << endl;
}
