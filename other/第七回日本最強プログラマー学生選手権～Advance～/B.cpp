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
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        vector<int> now;
        for (int j = 0; j < 10; j++) {
            if (i + j >= n) {
                break;
            }
            now.push_back(p[i + j]);
        }
        i += now.size() - 1;

        SORT(now);
        for (auto x : now) {
            ans.push_back(x);
        }
    }

    bool sorted = true;
    for (int i = 1; i < n; i++) {
        sorted &= (ans[i - 1] < ans[i]);
    }
    if (sorted) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
