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
    int N, K;
    cin >> N >> K;

    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
        P[i]--;
    }

    // ダブリング
    int maxLog = 64;
    // i番目の要素から2^j回移動した先の要素
    vector<vector<int>> next(N, vector<int>(maxLog));
    for (int i = 0; i < N; i++) {
        next[i][0] = P[P[i]];
    }

    for (int j = 1; j < maxLog; j++) {
        for (int i = 0; i < N; i++) {
            next[i][j] = next[next[i][j - 1]][j - 1];
        }
    }

    vector<int> result(N);
    for (int i = 0; i < N; i++) {
        int current = P[i];
        for (int j = 0; j < maxLog; j++) {
            if (K & (1LL << j)) {
                current = next[current][j];
            }
        }
        result[i] = current + 1;
    }

    for (int i = 0; i < N; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
