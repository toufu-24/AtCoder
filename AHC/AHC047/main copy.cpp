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

struct output {
    vector<char> C;
    vector<vector<int>> A;
};

int32_t main() {
    int _n, _m, _l;
    cin >> _n >> _m >> _l;
    constexpr int n = 36, m = 12, l = 1000000;
    vector<string> s(n);
    vector<int> p(n);
    map<string, int> score;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> p[i];
        score[s[i]] = p[i];
    }
    output ans;
    ans.C.resize(m);
    ans.A.resize(m, vector<int>(m));
    for (int i = 0; i < m; i++) {
        ans.C[i * 2] = 'A' + i;
        ans.C[i * 2 + 1] = 'A' + i;
    }
}
