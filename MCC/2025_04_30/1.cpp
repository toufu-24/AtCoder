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
    set<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        st.insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (!st.contains(i)) {
            continue;
        }
        st.erase(a[i]);
    }

    cout << st.size() << endl;
    for (auto x : st) {
        cout << x + 1 << " ";
    }
    cout << endl;
}
