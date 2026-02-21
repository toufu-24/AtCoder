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
    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a[i]; j++) {
                q.push(i);
            }
            for (int j = 0; j < b[i]; j++) {
                q.pop();
            }

            if (q.empty()) {
                continue;
            }
            int top = q.front();
            while (top <= i - d) {
                q.pop();
                if (q.empty()) {
                    break;
                }
                top = q.front();
            }
        }

        cout << q.size() << endl;
    }
}
