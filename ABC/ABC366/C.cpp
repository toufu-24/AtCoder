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
    int Q;
    cin >> Q;
    map<int, int> mp;
    while (Q--) {
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
            int x;
            cin >> x;
            mp[x]--;
            if (mp[x] == 0) {
                mp.erase(x);
            }
            break;
        }
        case 3: {
            cout << mp.size() << endl;
            break;
        }
        default:
            break;
        }
    }
}
