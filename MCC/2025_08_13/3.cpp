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
    queue<pair<int, int>> que;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, c;
            cin >> x >> c;
            que.push({x, c});
        } else if (op == 2) {
            int c;
            cin >> c;
            int tmp = 0;
            while (true) {
                if (c > que.front().second) {
                    tmp += que.front().first * que.front().second;
                    c -= que.front().second;
                    que.pop();
                } else {
                    tmp += que.front().first * c;
                    que.front().second -= c;
                    break;
                }
            }
            cout << tmp << endl;
        }
    }
}