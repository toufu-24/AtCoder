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

    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }

    bool ans = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) {
                if (sum[j] - sum[i] == s) {
                    ans = true;
                }
            } else {
                if (sum[n] - sum[i] + sum[j] == s) {
                    ans = true;
                }
            }
        }
    }
    cout << (ans ? "Yes" : "No") << endl;
}
