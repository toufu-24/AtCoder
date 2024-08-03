// #pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC target("tune=native")
#pragma GCC optimize("unroll-loops")

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

// #define int ll

int xorsum[200001];
int A[200000];

int32_t main() {
    ld start = clock();
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    cin >> N;
    // vector<int> A(N);
    // vector<int> xorsum(N + 1, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        xorsum[i + 1] = xorsum[i] ^ A[i];
    }

    ll ans = 0;
    for (int i = 0; i < N - 1; ++i) {
        // ここを高速にしたい
        for (int j = i + 1; j < N; ++j) {
            ans += xorsum[j + 1] ^ xorsum[i];
        }
    }

    cout << ans;
    ld end = clock();
    cerr << endl;
    cerr << "Time: " << (end - start) / CLOCKS_PER_SEC << "s" << endl;
}
