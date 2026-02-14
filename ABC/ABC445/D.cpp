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
    int H, W, n;
    cin >> H >> W >> n;
    map<int, set<int>> wmp, hmp;
    vector<int> h(n), w(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> w[i];
        hmp[h[i]].insert(i);
        wmp[w[i]].insert(i);
    }
    // cerr << "in" << endl;

    vector<pair<int, int>> ans(n);
    set<int> debug;
    int remain_h = H;
    int remain_w = W;
    for (int _ = 0; _ < n; _++) {
        // cerr << remain_h << " " << remain_w << endl;
        // 縦があるか
        if (hmp.contains(remain_h)) {
            auto itr = hmp[remain_h].begin();
            int idx = *itr;
            hmp[remain_h].erase(idx);
            if (hmp[remain_h].empty()) {
                hmp.erase(remain_h);
            }
            wmp[w[idx]].erase(idx);
            if (wmp[w[idx]].empty()) {
                wmp.erase(w[idx]);
            }
            ans[idx] = {H - remain_h, W - remain_w};
            remain_w -= w[idx];
            // if (debug.contains(idx)) {
            //     cerr << "same idx" << endl;
            //     assert(false);
            // }
            // debug.insert(idx);
        }
        // 横があるか
        else if (wmp.contains(remain_w)) {
            auto itr = wmp[remain_w].begin();
            int idx = *itr;
            wmp[remain_w].erase(idx);
            if (wmp[remain_w].empty()) {
                wmp.erase(remain_w);
            }
            hmp[h[idx]].erase(idx);
            if (hmp[h[idx]].empty()) {
                hmp.erase(h[idx]);
            }
            ans[idx] = {H - remain_h, W - remain_w};
            remain_h -= h[idx];
            // if (debug.contains(idx)) {
            //     cerr << "same idx" << endl;
            //     assert(false);
            // }
            // debug.insert(idx);
        } else {
            assert(false);
        }
    }

    // assert(remain_h == 0);
    // assert(remain_w == 0);
    for (auto x : ans) {
        cout << x.first + 1 << " " << x.second + 1 << endl;
    }
}
