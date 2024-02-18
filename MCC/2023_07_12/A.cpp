#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    vector<int> A(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> A[i];
    }
    sort(A);
    int ans = 0;
    if (A[0] % 2 != A[1] % 2)
    {
        ans += 4;
    }
    for (int i = 0; i < 2; i++)
    {
        ans += A[2] - A[i];
    }

    cout << ans / 2 << endl;
}