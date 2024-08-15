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
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    vector<int> bin(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (S[i][j] == 'o') {
                bin[i] |= (1 << j);
            }
        }
    }

    vector<int> perm(N);
    iota(all(perm), 0);
    int ans = 1e9;
    do {
        int mask = 0;
        for (int i = 0; i < N; i++) {
            mask |= bin[perm[i]];
            if (mask == (1 << M) - 1) {
                ans = min(ans, i + 1);
                break;
            }
        }
    } while (next_permutation(all(perm)));
    cout << ans << endl;
}
