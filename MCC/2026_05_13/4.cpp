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

int mypow(int n) {
    int ret = 1;
    for (int i = 0; i < n; i++) {
        ret *= 2;
    }
    return ret;
}

int32_t main() {
    int n;
    cin >> n;
    // vector<int> cnt(5, 0);
    map<char, int> mp;
    vector<string> s(n);
    set<int> march = {'M', 'A', 'R', 'C', 'H'};
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        if (march.contains(s[i][0]))
            mp[s[i][0]]++;
    }
    vector<int> cnt;
    for (auto [key, val] : mp) {
        cnt.push_back(val);
    }
    assert(cnt.size() <= 5);
    int ans = 0;
    vector<int> perm(5, 0);
    perm[0] = 1;
    perm[1] = 1;
    perm[2] = 1;
    SORT(perm);
    do {
        vector<int> can;
        for (int i = 0; i < 5; i++) {
            if (perm[i] == 1) {
                can.push_back(i);
            }
        }

        assert(can.size() == 3);
        int tmp = 1;
        tmp *= mypow(can[0]);
        tmp *= mypow(can[1]);
        tmp *= mypow(can[2]);
        if (cnt[0] == 0 || cnt[1] == 0 || cnt[2] == 0) {
            continue;
        }
        ans += tmp;

    } while (next_permutation(all(perm)));

    cout << ans << endl;
}
