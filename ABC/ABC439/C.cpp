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
    // map<int, int> mp;
    vector<int> tmp(1e7 + 1, 0);
    for (int x = 1; x < 1e4; x++) {
        for (int y = x + 1; y < 1e4; y++) {
            if (x * x + y * y > 1e7) {
                break;
            }
            tmp[x * x + y * y]++;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (tmp[i] == 1) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x << " ";
    }
}
