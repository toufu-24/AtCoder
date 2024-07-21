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
    int N, T, P;
    cin >> N >> T >> P;
    vector<int> L(N);
    for (int i = 0; i < N; i++) {
        cin >> L[i];
    }
    for (int i = 0; i <= 150; i++) { 
        int cnt = 0;
        for (int j = 0; j < N; j++) {
            if (L[j] >= T) {
                cnt++;
            }
        }
        if (cnt >= P) {
            cout << i << endl;
            return 0;
        }

        for (int j = 0; j < N; j++) {
            L[j]++;
        }
    }
}
