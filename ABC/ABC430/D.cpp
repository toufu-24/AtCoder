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

int f(int a, int b) {
    return abs(a - b);
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    int ans = 0;
    set<int> st;
    map<int, int> place_to_score;
    st.insert(0);
    st.insert(x[0]);
    place_to_score[0] = x[0];
    place_to_score[x[0]] = x[0];
    ans += x[0] * 2;
    cout << ans << endl;
    for (int i = 1; i < n; i++) {
        auto itr = st.lower_bound(x[i]);
        auto next = itr;
        auto prev = --itr; // これはできるはず

        if (next == st.end()) {
            if (place_to_score[*prev] > f(*prev, x[i])) {
                ans -= place_to_score[*prev];
                place_to_score[*prev] = f(*prev, x[i]);
                ans += place_to_score[*prev];
            }
            place_to_score[x[i]] = f(*prev, x[i]);
            ans += f(*prev, x[i]);
        } else {
            // prev
            if (place_to_score[*prev] > f(*prev, x[i])) {
                ans -= place_to_score[*prev];
                place_to_score[*prev] = f(*prev, x[i]);
                ans += place_to_score[*prev];
            }
            // next
            if (place_to_score[*next] > f(*next, x[i])) {
                ans -= place_to_score[*next];
                place_to_score[*next] = f(*next, x[i]);
                ans += place_to_score[*next];
            }
            // x[i]
            place_to_score[x[i]] = min(f(*prev, x[i]), f(*next, x[i]));
            ans += min(f(*prev, x[i]), f(*next, x[i]));
        }
        cout << ans << endl;
        st.insert(x[i]);
    }
}
