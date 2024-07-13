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
    vector<int> L(N), R(N);
    for (int i = 0; i < N; i++) {
        cin >> L[i] >> R[i];
    }
    int diff = reduce(all(R)) - reduce(all(L));
    vector<int> tmp = L;
    int L_sum = reduce(all(L));
    if (L_sum <= 0 && 0 <= L_sum + diff) {
        cout << "Yes" << endl;
        int plus = 0 - L_sum;
        for (int i = 0; i < N; i++) {
            if (plus > 0) {
                int add = min(plus, R[i] - L[i]);
                cout << L[i] + add << " ";
                plus -= add;
            } else {
                cout << L[i] << " ";
            }
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }
}
