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
    queue<int> que;
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            que.push(x);
        } else {
            cout << que.front() << endl;
            que.pop();
        }
    }
}
