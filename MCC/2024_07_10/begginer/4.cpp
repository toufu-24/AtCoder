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
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    SORT(A);
    set<int> st;
    for (int i = 0; i < N; i++) {
        if (st.size() < K) {
            if (st.contains(A[i])) {
                continue;
            } else {
                st.insert(A[i]);
            }
        }
    }

    for (int i = 0; i < 1e9; i++) {
        if (!st.contains(i)) {
            cout << i << endl;
            break;
        }
    }
}
