#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, T;
    cin >> N >> T;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int cnt = 0;
    int max_diff = 0;
    int min_value = A[0];
    for (int i = 1; i < N; i++)
    {
        if (A[i] - min_value > max_diff)
        {
            max_diff = A[i] - min_value;
            cnt = 1;
        }
        else if (A[i] - min_value == max_diff)
        {
            cnt++;
        }
        min_value = min(min_value, A[i]);
    }
    cout << min(cnt, T * max_diff) << endl;
}
