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
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    a.push_back(0);
    a.push_back(n + 1);
    SORT(a);

    vector<int> width(a.size() - 1);
    for (int i = 0; i < width.size(); i++) {
        int diff = a[i + 1] - a[i] - 1;
        if (diff == 0) {
            diff = 1e18;
        }
        width[i] = diff;
    }
    int stamp = *min_element(all(width));
    int ans = 0;
    for (int i = 0; i < width.size(); i++) {
        if (width[i] == 1e18) {
            width[i] = 0;
        }
        ans += width[i] / stamp + (width[i] % stamp != 0);
    }
    cout << ans << endl;
}
