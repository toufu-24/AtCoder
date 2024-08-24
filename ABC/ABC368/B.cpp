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
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int ans = 0;
    while (a.size() > 1) {
        SORT(a);
        a[a.size() - 1]--, a[a.size() - 2]--;
        if (a[a.size() - 2] <= 0) {
            if (a[a.size() - 1] <= 0) {
                a.pop_back();
                a.pop_back();
            } else
                a.erase(a.begin() + a.size() - 2);
        } else if (a[a.size() - 1] <= 0) {
            a.pop_back();
        }
        ans++;
    }
    cout << ans << endl;
}
