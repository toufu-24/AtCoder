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
    string n;
    cin >> n;
    string ans;
    while (n != 0) {
        ans.push_back(n % 26 + 'a');
        n /= 26;
    }
    REVERSE(ans);
    for (auto c : ans) {
        cout << char(c - 1);
    }
}
