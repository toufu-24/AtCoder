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
    int N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        P[i]--;
    }

    // priority_queue<int, vector<int>, greater<int>> pq;
    // set<int> st;
    dsu d(N);
    map<int, int> mp;
    vector<int> ans(N, -1);
    for (int i = 0; i < N; i++) {
        auto itr = mp.lower_bound(P[i]);
        if (itr == mp.end()) {
            mp[P[i]] = 1;
        } else {
            mp[P[i]] = itr->second + 1;
            d.merge(P[i], itr->first);
            mp.erase(itr);
        }
        if (mp[P[i]] == K) {
            ans[P[i]] = i;
            mp.erase(P[i]);
        }
    }

    auto groups = d.groups();
    for (auto group : groups) {
        vector<int> v;
        int val = -1;
        for (int i : group) {
            if (ans[i] != -1) {
                val = ans[i];
                break;
            }
        }
        for (int i : group) {
            if (ans[i] == -1) {
                ans[i] = val;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (ans[i] == -1) {
            cout << -1 << endl;
        } else
            cout << ans[i] + 1 << endl;
    }
}
