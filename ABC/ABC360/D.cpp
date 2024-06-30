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
    int N, T;
    cin >> N >> T;
    string S;
    cin >> S;
    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        X[i] += 1e9;
    }
    vector<pair<int, int>> one_idx, zero_idx;
    vector<int> one, zero;
    for (int i = 0; i < N; i++) {
        if (S[i] == '1') {
            one_idx.push_back({X[i], i});
        } else {
            zero_idx.push_back({X[i], i});
        }
    }
    SORT(one_idx);
    SORT(zero_idx);
    for (int i = 0; i < one_idx.size(); i++) {
        one.push_back(one_idx[i].first);
    }
    for (int i = 0; i < zero_idx.size(); i++) {
        zero.push_back(zero_idx[i].first);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] == '1') {
            int overidx = upper_bound(zero.begin(), zero.end(), 2 * T + X[i]) -
                          zero.begin();
            int loweridx =
                lower_bound(zero.begin(), zero.end(), X[i]) - zero.begin();
            ans += overidx - loweridx;
        }
    }
    cout << ans << endl;
}
