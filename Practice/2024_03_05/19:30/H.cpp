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
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    multiset<int> ms;
    for (int i = 0; i < M; i++)
    {
        ms.insert(A[i]);
    }
    int sum = 0;
    for (int i = 0; i < K; i++)
    {
        sum += *ms.begin();
        ms.erase(ms.begin());
    }

    for (int i = 0; i < N - M; i++)
    {
        ms.insert(A[i + M]);
        if (ms.find(A[i]) != ms.end())
        {
            ms.erase(ms.find(A[i]));
        }
        sum += *ms.begin();
    }
}