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
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    // auto np = p;
    // int k = 0;
    // for (int i = 0; i < n; i++) {
    //     if (np[i] != i + 1) {
    //         swap(np[i], np[np[i] - 1]);
    //         k++;
    //         i--;
    //     }
    // }

    set<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        if (p[i] == i) {
            continue;
        }
        st.insert(minmax(i, p[i]));
        int tmp = p[i];
        set<int> stt;
        stt.insert(i);
        stt.insert(p[i]);
        for (int j = 0; j < n; j++) {
            tmp = p[tmp];
            if (stt.contains(tmp)) {
                break;
            }
            st.insert(minmax(i, tmp));
        }
    }
    cout << st.size() << endl;
    for (auto [x, y] : st) {
        cout << x << " " << y << endl;
    }
}
