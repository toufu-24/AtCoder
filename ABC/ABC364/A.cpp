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
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    bool sweet = false;
    for (int i = 0; i < N; i++) {
        if (S[i] == "sweet") {
            if (sweet) {
                if (i == N - 1) {
                    cout << "Yes" << endl;
                    return 0;
                }
                cout << "No" << endl;
                return 0;
            }
            sweet = true;
        } else {
            sweet = false;
        }
    }
    cout << "Yes" << endl;
}
