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
    int smaller_sum = 0;
    for (int i = 1; i < N - 1; i++)
    {
        smaller_sum += A[i];
    }
    int larger_sum = 0;
    for (int i = 0; i < N - 2; i++)
    {
        larger_sum += A[i];
    }

    if (X - (sum - maximum - minimum) < 0)
    {
        cout << 0 << endl;
        return 0;
    }
    if (X - (sum - maximum - minimum) > 100)
    {
        cout << -1 << endl;
        return 0;
    }
    cout << X - (sum - maximum - minimum) << endl;
}