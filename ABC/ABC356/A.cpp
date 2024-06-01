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

int32_t main()
{
    int N, L, R;
    cin >> N >> L >> R;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        A[i] = i + 1;
    }
    reverse(A.begin() + L - 1, A.begin() + R);
    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
}
