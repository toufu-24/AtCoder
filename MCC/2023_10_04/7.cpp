#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    SORT(A);
    SORT(B);
    int left = -1;
    int right = 1e9 + 10;
    while (right - left > 1)
    {
        int mid = (right + left) / 2;
        int seller = upper_bound(all(A), mid) - A.begin();
        int buyer = M - (lower_bound(all(B), mid) - B.begin());
        if (seller >= buyer)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << right;
}