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

string myplus(vector<string> vec) {
    string ret;
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        REVERSE(vec[i]);
    }

    // int size = max(a.size(), b.size());
    int size = 0;
    for (int i = 0; i < n; i++) {
        size = max<int>(size, vec[i].size());
    }

    for (int i = 0; i < n; i++) {
        while (vec[i].size() < size) {
            vec[i].push_back('0');
        }
        assert(vec[i].size() == size);
    }
    int up = 0;
    // cerr << a << " " << b << endl;
    for (int i = 0; i < size; i++) {
        int sum = up + (a[i] - '0') + (b[i] - '0');
        string sum_s = to_string(sum);
        // cerr << sum_s << endl;
        assert(sum_s.size() <= 2);
        REVERSE(sum_s);
        if (sum_s.size() == 2) {
            up = sum_s[1] - '0';
        } else {
            up = 0;
        }
        ret.push_back(sum_s[0]);
    }
    if (up != 0) {
        ret.push_back(up + '0');
    }
    REVERSE(ret);
    return ret;
}

int32_t main() {
    string s;
    cin >> s;

    string ans = "0";
    while (s.size() > 0) {
        ans = myplus(ans, s);
        s.pop_back();
    }
    cout << ans << endl;
}