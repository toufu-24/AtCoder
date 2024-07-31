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
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    vector<int> Q(N);
    for (int i = 0; i < N; i++) {
        cin >> Q[i];
    }

    vector<int> perm(N);
    iota(all(perm), 1);
    int a = 0, b = 0;
    int idx = 0;
    do {
        if (perm == P) {
            a = idx;
        }
        if (perm == Q) {
            b = idx;
        }
        idx++;
    } while (next_permutation(all(perm)));
    cout << abs(a - b) << endl;
}
