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
    int s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int a_sum = reduce(all(a));
    s %= a_sum;

    for (int i = 0; i < n; i++) {
        a.push_back(a[i]);
    }
    n *= 2;
    bool ans = false;
    int left = 0, right = 0;
    int now = 0;
    while (left < n) {
        while (right < n && now < s) {
            now += a[right];
            right++;
        }
        if (now == s) {
            ans = true;
            break;
        }
        now -= a[left];
        left++;
    }
    cout << (ans ? "Yes" : "No") << endl;
}
