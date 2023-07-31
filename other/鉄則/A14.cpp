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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);
    vector<int> D(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> D[i];
    }

    vector<int> P(N * N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            P[i * N + j] = A[i] + B[j];
        }
    }
    sort(P);
    vector<int> Q(N * N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Q[i * N + j] = C[i] + D[j];
        }
    }
    sort(Q);

    for (int i = 0; i < N * N; i++)
    {
        if (binary_search(all(P), K - Q[i]))
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}