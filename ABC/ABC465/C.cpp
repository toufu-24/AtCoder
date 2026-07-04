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
    string s;
    cin >> s;
    deque<int> ans;
    int add = 1;
    bool left = true;
    for (auto c : s) {
        if (left) {
            ans.push_front(add);
        } else {
            ans.push_back(add);
        }
        if (c == 'o') {
            left = !left;
        }
        // cout << add << " " << left << endl;
        add++;
    }

    if (left) {
        REVERSE(ans);
    }

    for (auto x : ans) {
        cout << x << " ";
    }
}

// . 左右右左