#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, K;
    cin >> N >> K;
    int sum = K * (K + 1) / 2;
    cerr << sum << endl;
    set<int> st;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (A[i] > K)
        {
            continue;
        }
        if (!st.contains(A[i]))
        {
            sum -= A[i];
            st.insert(A[i]);
        }
    }
    cout << sum << endl;
}
