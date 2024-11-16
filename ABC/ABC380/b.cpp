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
    vector<int> ans;
    for (int i = 0; i < s.size(); i++) {
        int cnt = 0;
        for (int j = i; j < s.size(); j++, i++) {
            if (s[j] == '|') {
                break;
            }
            cnt++;
        }
        ans.push_back(cnt);
    }
    for (int i = 1; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
}
