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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> puyo;
    for (int i = 0; i < n; i++) {
        puyo.push_back(a[i]);
        bool ok = true;
        while (ok && puyo.size() >= 4) {
            for (int i = 0; i < 4; i++) {
                if (puyo[puyo.size() - i - 1] != puyo.back()) {
                    ok = false;
                }
            }
            if (ok) {
                for (int i = 0; i < 4; i++) {
                    puyo.pop_back();
                }
            }
        }
    }

    cout << puyo.size() << endl;
}
