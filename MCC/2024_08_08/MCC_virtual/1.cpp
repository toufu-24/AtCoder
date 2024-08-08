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
    vector<int> dice(3);
    for (int i = 0; i < 3; i++) {
        cin >> dice[i];
    }
    SORT(dice);
    for (int i = 0; i < 2; i++) {
        if (dice[i] == dice[i + 1]) {
            for (int j = 0; j < 3; j++) {
                if (j != i && j != i + 1) {
                    cout << dice[j] << endl;
                    return 0;
                }
            }
        }
    }
    cout << 0 << endl;
}
