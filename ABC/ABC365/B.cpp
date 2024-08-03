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
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int maxA = 0;
    int maxi = 0;
    int maxA2 = 0;
    int max2i = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > maxA) {
            maxA2 = maxA;
            max2i = maxi;
            maxA = A[i];
            maxi = i;
        } else if (A[i] > maxA2) {
            maxA2 = A[i];
            max2i = i;
        }
    }
    cout << max2i + 1 << endl;
}
