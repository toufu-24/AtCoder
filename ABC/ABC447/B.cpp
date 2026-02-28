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
    vector<int> ch(26, 0);
    for (auto c : s) {
        ch[c - 'a']++;
    }
    int ma = *max_element(all(ch));
    for (auto c : s) {
        if (ch[c - 'a'] != ma) {
            cout << c;
        }
    }
    cout << endl;
}
