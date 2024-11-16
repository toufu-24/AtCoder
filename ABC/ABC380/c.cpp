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
    string s;
    cin >> s;

    int cnt = 0;
    vector<int> ones_idx, ones_length;
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        bool flag = true;
        for (int j = i; j < n; j++, i++) {
            if (s[j] == '0') {
                if (!flag) {
                    ones_length.push_back(tmp);
                }
                break;
            }
            tmp++;
            if (flag) {
                cnt++;
                ones_idx.push_back(j);
                flag = false;
            }
        }
        if (i == n && !flag) {
            ones_length.push_back(tmp);
        }
    }
    k--;
    string prev, mid, ones, next;
    prev = s.substr(0, ones_idx[k - 1]);
    mid = s.substr(ones_idx[k - 1], ones_idx[k] - ones_idx[k - 1]);
    ones = s.substr(ones_idx[k], ones_length[k]);
    next = s.substr(ones_idx[k] + ones_length[k]);

    cout << prev << ones << mid << next << endl;
}
