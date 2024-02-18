#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll
signed main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    for (int q = 0; q < Q; q++)
    {
        int K;
        cin >> K;
        int left = -1, right = LLONG_MAX / 2;
        while (abs(right - left) > 1)
        {
            int mid = (right + left) / 2;
            int idx = lower_bound(all(A), mid) - A.begin();
            int num = mid - idx;
            if (num > K)
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        cout << left << endl;
    }
}