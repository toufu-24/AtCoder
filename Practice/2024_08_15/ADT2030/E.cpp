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
    map<int, int> mp;
    while (q--) {
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int x;
            cin >> x;
            mp[x]++;
            break;
        }
        case 2: {
            int x, c;
            cin >> x >> c;
            mp[x] -= min(mp[x], c);
            if (mp[x] == 0) {
                mp.erase(x);
            }
            break;
        }
        case 3: {
            cout << mp.rbegin()->first - mp.begin()->first << endl;
            break;
        }
        }
    }
}