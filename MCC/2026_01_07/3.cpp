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

    stack<pair<int, int>> st;
    st.push({-1, -1});
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans++;
        auto top = st.top();
        st.pop();
        if (a[i] == top.first) {
            top.second++;
            if (top.second != top.first) {
                st.push(top);
            } else {
                ans -= top.first;
            }
        } else {
            st.push(top);
            st.push({a[i], 1});
        }
        cout << ans << endl;
    }
}