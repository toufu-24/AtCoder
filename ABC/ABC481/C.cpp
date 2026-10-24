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
    int q;
    cin >> q;
    map<string, int> mp;
    int idx = 1;
    while (q--) {
        string s;
        cin >> s;
        if(!mp.contains(s)){
            mp[s] = idx++;
        }
        cout << mp[s] << endl;
    }
}
