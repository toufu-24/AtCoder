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
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    for (int i = 0; i < M; i++)
    {
        int C = 0;
        int num = A[B[i]];
        A[B[i]] = 0;
        for (int j = 0; j < num; j++)
        {
            C++;
            int idx = (B[i] + C) % N;
            A[idx]++;
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
}