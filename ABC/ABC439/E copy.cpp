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

// 閉区間
bool iscontain(set<pair<int, int>> &st, int left, int right) {
    auto itr = st.lower_bound({left, 0});
    if (itr == st.end()) {
        return false;
    }
    auto [l, r] = *itr;
    if (l <= right) {
        return true;
    } else {
        return false;
    }
}

bool addInterval(set<pair<int, int>> &st, int left, int right) {
    if (iscontain(st, left, right)) {
        cerr << "false" << endl;
        return false;
    }
    st.insert({left, right});
    return true;
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<pair<int, int>> tmp(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        tmp[i] = {abs(b[i] - a[i]), i};
    }
    SORT(tmp);
    int ans = 0;
    set<pair<int, int>> kukan;
    for (int i = 0; i < n; i++) {
        auto [diff, idx] = tmp[i];
        ans += addInterval(kukan, a[idx], b[idx]);
    }
    cout << ans << endl;
}
