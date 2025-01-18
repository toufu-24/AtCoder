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
    int front = 0;
    int deleted = 0;
    vector<int> v;
    v.push_back(0);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l;
            cin >> l;
            v.push_back(v.back() + l);
        } else if (t == 2) {
            front++;
            deleted = v[front];
        } else {
            int k;
            cin >> k;
            cout << v[front + k - 1] - deleted << endl;
        }
    }
}
