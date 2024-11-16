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
    vector<int> cnt(10, 0);
    string s = to_string(n);
    for (char c : s) {
        cnt[c - '0']++;
    }
    bool ans = true;
    if (cnt[1] == 1 && cnt[2] == 2 && cnt[3] == 3) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}
