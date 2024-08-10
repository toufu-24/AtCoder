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
    int N;
    cin >> N;
    vector<string> S(N);
    int max_size = 0;
    for (int i = 0; i < N; i++) {
        cin >> S[i];
        max_size = max(max_size, (int)S[i].size());
    }

    vector<string> ans(max_size, "");
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < max_size; j++) {
            if (j < S[i].size()) {
                ans[j] += S[i][j];
            } else {
                ans[j] += "*";
            }
        }
    }

    for (int i = 0; i < max_size; i++) {
        while (ans[i].back() == '*') {
            ans[i].pop_back();
        }
        cout << ans[i] << endl;
    }
}
