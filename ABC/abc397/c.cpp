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
    vector<int> cnt(N, 0);
    // set<int> s;
    map<int, int> prev, next;
    for (int i = 0; i < N; i++) {
        next[A[i]]++;
    }

    int ans = 0;
    for (int i = 0; i < N - 1; i++) {
        prev[A[i]]++;
        next[A[i]]--;
        if (next[A[i]] == 0) {
            next.erase(A[i]);
        }
        ans = max<int>(ans, prev.size() + next.size());
    }
    cout << ans << endl;
}
