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
    vector<int> kind_sum(n);
    set<int> tmp;
    for (int i = 0; i < n; i++) {
        tmp.insert(a[i]);
        kind_sum[i] = tmp.size();
    }
    tmp.clear();
    vector<int> kind_sum_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        tmp.insert(a[i]);
        kind_sum_sum[i + 1] = kind_sum_sum[i] + tmp.size();
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        // set<int> st;
        // for (int j = i; j < n; j++) {
        //     st.insert(a[j]);
        //     ans += st.size();
        // }
        int add = kind_sum_sum[n] - kind_sum_sum[i] * (n - i);
        ans += add;
    }
    cout << ans << endl;
}
