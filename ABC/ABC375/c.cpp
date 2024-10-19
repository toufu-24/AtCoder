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
    assert(n % 2 == 0);
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n / 2; i++) {
        auto ori_a = a;
        for (int x = i; x < n - i; x++) {
            for (int y = i; y < n - i; y++) {
                a[y][n - x - 1] = ori_a[x][y];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}
