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
    vector<int> a(5);
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        if (a[i] > a[i + 1]) {
            cnt++;
            swap(a[i], a[i + 1]);
        }
    }
    if (cnt == 1) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
