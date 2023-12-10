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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> P(N, 0);
    for (int i = 1; i < N; i++)
    {
        cin >> P[i];
        P[i]--;
    }
    vector<int> after;
    after = A;
    for (int loop = 0; loop < 100; loop++)
    {
        for (int i = 1; i < N; i++)
        {
            after[P[i]] += after[i];
        }
    }
}