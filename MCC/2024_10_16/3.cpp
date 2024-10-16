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

    int ans = 0;
    int max_ans = 0;
    for (int i = 2; i <= 1000; i++) {
        int tmp = 0;
        for (int j = 0; j < n; j++) {
            tmp += a[j] % i == 0;
        }
        if (tmp > max_ans) {
            max_ans = tmp;
            ans = i;
        }
    }
    cout << ans << endl;
}
