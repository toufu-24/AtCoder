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
    string circle(K, 'O');

    int ans = 0;
    for (int i = K - 1; i < N; i++) {
        string tmp = S.substr(i - K + 1, K);

        if (tmp == circle) {
            ans++;
            for (int j = i - K + 1; j <= i; j++) {
                S[j] = 'X';
            }
        }
    }

    cout << ans << endl;
}
