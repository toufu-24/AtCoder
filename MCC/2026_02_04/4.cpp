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
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<int> dot;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.')
            dot.push_back(i);
    }

    int left = 0, right = k + 1;
    if (dot.size() <= k) {
        cout << s.size() << endl;
        return 0;
    }

    int ans = 0;
    while (right < dot.size()) {
        // cerr << dot[left] << " " << dot[right] << endl;
        ans = max(ans, ((dot[right] - 1) - (dot[left] + 1) + 1));
        // cerr << "ans= " << ans << endl;
        left++, right++;
    }
    dot.push_back(s.size());
    // 前から
    ans = max(ans, dot[k]);
    // cerr << dot[k] << endl;
    // 後ろから
    ans = max(ans, (int)s.size() - dot[dot.size() - k - 1]);
    // cerr << (int)s.size() - dot[dot.size() - k - 1] << endl;
    cout << ans << endl;
}
