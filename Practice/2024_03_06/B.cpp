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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    queue<int> q;
    for (int i = 0; i < N; i++)
    {
        q.push(A[i]);
    }
    for (int i = 0; i < K; i++)
    {
        q.pop();
        q.push(0);
    }

    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
}