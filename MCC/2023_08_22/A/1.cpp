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
    int H, N;
    cin >> H >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    ll sum = accumulate(all(A), 0);
    if (sum >= H)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}