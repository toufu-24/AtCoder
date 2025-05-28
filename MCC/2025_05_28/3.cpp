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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vector<int> prev(n, -1);
    int now = 0;
    for (int i = 0; i < k; i++) {
        if (prev[now] != -1) {
            int shuuki = i - prev[now];
            int amari = (k - i) % shuuki;
            for (int j = 0; j < amari; j++) {
                now = a[now];
            }
            cout << now + 1 << endl;
            return 0;
        }
        prev[now] = i;
        now = a[now];
    }
    cout << now + 1 << endl;
}
