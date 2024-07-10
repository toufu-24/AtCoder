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
    int N, S, K;
    cin >> N >> S >> K;
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int p, q;
        cin >> p >> q;
        sum += p * q;
    }
    if (sum < S) {
        sum += K;
    }
    cout << sum;
}
