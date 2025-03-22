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
    vector<int> a(7);
    for (int i = 0; i < 7; i++) {
        cin >> a[i];
        a[i]--;
    }
    SORT(a);
    vector<int> cnt(13, 0);
    for (int i = 0; i < 7; i++) {
        cnt[a[i]]++;
    }
    int over_3 = 0, two = 0;
    for (int i = 0; i < 13; i++) {
        if (cnt[i] >= 3) {
            over_3++;
        }
        if (cnt[i] == 2) {
            two++;
        }
    }
    if (over_3 >= 2) {
        cout << "Yes" << endl;
    } else if (over_3 >= 1 && two >= 1) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
