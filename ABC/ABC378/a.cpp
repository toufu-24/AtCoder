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
    vector<int> a(4);
    for (int i = 0; i < 4; i++) {
        cin >> a[i];
    }
    SORT(a);
    int cnt = 0;
    for (int i = 0; i < int(a.size()) - 1; i++) {
        if (i >= int(a.size()) - 1) {
            break;
        }
        if (a[i] == a[i + 1]) {
            cnt++;
            a.erase(a.begin() + i);
            a.erase(a.begin() + i);
            i = -1;
            SORT(a);
        }
    }
    cout << cnt << endl;
}
