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
    int n, q;
    cin >> n >> q;
    vector<int> back(n, -1), front(n, -1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            back[x] = y;
            front[y] = x;
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            back[x] = -1;
            front[y] = -1;
        } else {
            int x;
            cin >> x;
            x--;
            vector<int> ans;
            int now = x;
            bool flag = true;
            while (now != -1) {
                if (flag) {
                    flag = false;
                } else {
                    ans.push_back(now);
                }
                now = front[now];
            }
            REVERSE(ans);
            now = x;
            while (now != -1) {
                ans.push_back(now);
                now = back[now];
            }
            cout << ans.size() << " ";
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] + 1 << " ";
            }
            cout << endl;
        }
    }
}
