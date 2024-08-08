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
    priority_queue<int, vector<int>, greater<int>> pq; // 前
    queue<int> q;                                      // 後ろ
    while (Q--) {
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int x;
            cin >> x;
            q.push(x);
            break;
        }
        case 2: {
            if (pq.empty()) {
                cout << q.front() << endl;
                q.pop();
            } else {
                cout << pq.top() << endl;
                pq.pop();
            }
            break;
        }
        case 3: {
            while (!q.empty()) {
                pq.push(q.front());
                q.pop();
            }
            break;
        }
        default:
            break;
        }
    }
}
