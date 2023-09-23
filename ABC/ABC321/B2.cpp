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

int main()
{
    int N, X;
    cin >> N >> X;
    vector<int> A(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> A[i];
    }
    RSORT(A);
    int maximum = A[0];
    int minimum = A[N - 2];
    int sum = accumulate(all(A), 0);
    // 0 を加えた時
    int small = sum - maximum;
    if (small >= X)
    {
        cout << 0 << endl;
        return 0;
    }
    // 100 を加えた時
    int large = sum - minimum;
    if (large < X)
    {
        cout << -1 << endl;
        return 0;
    }
    // 1 ~ 99 を加えた時
    cout << X - (sum - maximum - minimum) << endl;
}