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

// #define int ll

int count_occurrences(const string &S, const string &T, const vector<int> &sa) {
    int n = S.size(), m = T.size();
    auto compare = [&](int i, const string &t) {
        return S.compare(i, t.size(), t) < 0;
    };
    auto compare2 = [&](const string &t, int i) {
        return S.compare(i, t.size(), t) > 0;
    };

    int lower = lower_bound(sa.begin(), sa.end(), T, compare) - sa.begin();
    int upper = upper_bound(sa.begin(), sa.end(), T, compare2) - sa.begin();

    return upper - lower;
}

int32_t main() {
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    vector<string> T(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i];
    }
    auto sa = suffix_array(S);
    for (int i = 0; i < Q; i++) {
        cout << count_occurrences(S, T[i], sa) << endl;
    }
}
