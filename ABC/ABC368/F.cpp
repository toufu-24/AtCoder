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

vector<pair<int, int>> prime_factorize(int N) {
    vector<pair<int, int>> res;
    for (int a = 2; a * a <= N; ++a) {
        if (N % a != 0)
            continue;
        int ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1)
        res.push_back({N, 1});
    return res;
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<pair<int, int>>> prime(n);
    for (int i = 0; i < n; i++) {
        prime[i] = prime_factorize(a[i]);
    }

    int nim = 0;
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < prime[i].size(); j++) {
            tmp += prime[i][j].second;
        }
        nim ^= tmp;
    }
    if (nim == 0) {
        cout << "Bruno" << endl;
    } else {
        cout << "Anna" << endl;
    }
    cerr << bitset<10>(nim) << endl;
}
