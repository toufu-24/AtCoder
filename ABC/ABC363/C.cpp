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
    string S;
    cin >> S;
    SORT(S);
    int ans = 0;
    do {
        bool ok = true;
        for (int i = 0; i < N - K + 1; i++) {
            string substr = S.substr(i, K);
            string rev = substr;
            REVERSE(rev);
            // 回文
            if (substr == rev) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans++;
        }
    } while (next_permutation(all(S)));
    cout << ans << endl;
}
