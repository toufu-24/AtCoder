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
    vector<tuple<int, int, int>> present(n);
    for (int i = 0; i < n; i++) {
        int p, a, b;
        cin >> p >> a >> b;
        present[i] = {p, a, b};
    }
}
