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
    string s, t;
    cin >> s >> t;

    deque<char> sde;
    for (auto c : s) {
        sde.push_back(c);
    }

    int ans = 0;
    bool ok = true;
    for (int i = 0; i < t.size(); i++) {
        if (sde.empty()) {
            // assert(t[i] == 'A');
            ok &= (t[i] == 'A');
            ans++;
        } else if (t[i] == sde.front()) {
            sde.pop_front(); // 正常
        } else {
            if (t[i] == 'A') {
                ans++; // sの前にA足し
            } else {
                ans++;
                // assert(sde.front() == 'A');
                ok &= (sde.front() == 'A');
                sde.pop_front();
                i--;
            }
        }
    }
    for (auto c : sde) {
        ok &= (sde.front() == 'A');
        sde.pop_front();
        ans++;
    }
    // assert(sde.empty());
    if (ok) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}
