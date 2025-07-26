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

int mpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int32_t main() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int p = mpow(n, k);
    vector<string> con;
    for (int i = 0; i < p; i++) {
        int now_idx = i;
        int tmp = now_idx;
        int tmp_k = k;
        vector<int> shinnsuu(tmp_k, 0);
        while (tmp > 0) {
            shinnsuu[tmp_k - 1] = tmp % n;
            tmp /= n;
            tmp_k--;
        }
        REVERSE(shinnsuu);
        string tmp_s = "";
        for (int j = 0; j < shinnsuu.size(); j++) {
            tmp_s += s[shinnsuu[j]];
        }
        con.push_back(tmp_s);
    }

    SORT(con);
    cout << con[x - 1] << endl;
}
