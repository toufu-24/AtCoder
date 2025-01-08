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
    pair<int, int> a, b, c, d;
    cin >> a.first >> a.second >> b.first >> b.second;
    cin >> c.first >> c.second >> d.first >> d.second;
    bool ans = true;
    vector<pair<int, int>> p = {a, b, c, d};
    vector<ld> theta_v(4);
    for (int i = 0; i < 4; i++) {
        pair<int, int> ba = {p[i].first - p[(i + 1) % 4].first, p[i].second - p[(i + 1) % 4].second};
        pair<int, int> bc = {p[(i + 2) % 4].first - p[(i + 1) % 4].first, p[(i + 2) % 4].second - p[(i + 1) % 4].second};
        int naiseki = ba.first * bc.first + ba.second * bc.second;
        int abNorm = ba.first * ba.first + ba.second * ba.second;
        int bcNorm = bc.first * bc.first + bc.second * bc.second;
        ld cosTheta = (ld)naiseki / sqrtl(abNorm) / sqrtl(bcNorm);
        ld theta = acos(cosTheta);
        if (!(0 <= theta && theta < M_PI)) {
            ans = false;
        }
        // cout << theta << endl;
        theta_v[i] = theta;
    }
    ld sum = reduce(all(theta_v));
    if (abs(sum - 2 * M_PI) < 1e-6) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
