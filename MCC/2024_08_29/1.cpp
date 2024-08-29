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
    SORT(a);
    int k;
    cin >> k;
    if (a[4] - a[0] > k) {
        cout << ":(" << endl;
    } else {
        cout << "Yay!" << endl;
    }
}
