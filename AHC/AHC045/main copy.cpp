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

constexpr int N = 800;
constexpr int Q = 400;

struct able_place {
    int lx, rx, ly, ry;
};

int32_t main() {
    int _N, M, _Q, L, W;
    cin >> _N >> M >> _Q >> L >> W;
    vector<int> G(M);
    for (int i = 0; i < M; i++) {
        cin >> G[i];
    }
    vector<able_place> places(N);
    for (int i = 0; i < N; i++) {
        cin >> places[i].lx >> places[i].rx >> places[i].ly >> places[i].ry;
    }
}
