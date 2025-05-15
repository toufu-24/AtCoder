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
    int n, x;
    cin >> n >> x;
    x--;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    int cnt = 1;
    set<int> st;
    st.insert(x);
    int next = a[x];
    while (!st.contains(next)) {
        st.insert(next);
        next = a[next];
        cnt++;
    }
    cout << cnt << endl;
}
