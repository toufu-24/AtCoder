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
    vector<string> s(12);
    int cnt = 0;
    for (int i = 0; i < 12; i++) {
        cin >> s[i];
        if (s[i].size() == i + 1) {
            cnt++;
        }
    }
    cout << cnt << endl;
}
