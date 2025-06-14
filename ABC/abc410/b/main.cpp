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
    int n, q;
    cin >> n >> q;
    vector<int> x(q);
    for (int i = 0; i < q; i++) {
        cin >> x[i];
        x[i]--;
    }
    vector<vector<int>> ball(n);
    for (int i = 0; i < q; i++) {
        if (x[i] == -1) {
            int min_idx = 0;
            int min_size = 1000000000;
            for (int j = 0; j < n; j++) {
                if (ball[j].size() < min_size) {
                    min_idx = j;
                    min_size = ball[j].size();
                }
            }
            ball[min_idx].push_back(i);
        } else {
            ball[x[i]].push_back(i);
        }
    }

    for (int i = 0; i < q; i++) {
        int idx = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < ball[j].size(); k++) {
                if (ball[j][k] == i) {
                    idx = j;
                    break;
                }
            }
        }
        cout << idx + 1 << " ";
    }
}
