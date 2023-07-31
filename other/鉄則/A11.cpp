#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, X;
    cin >> N >> X;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int left = 0;
    int right = N;
    while (right - left > 1)
    {
        int mid = (left + right) / 2;
        if (A[mid] > X)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    cout << left + 1;
}