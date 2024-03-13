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
    int M;
    cin >> M;
    vector<int> B(M);
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    int L;
    cin >> L;
    vector<int> C(L);
    for (int i = 0; i < L; i++)
    {
        cin >> C[i];
    }
    set<int> sum;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            for (int k = 0; k < L; k++)
            {
                sum.insert(A[i] + B[j] + C[k]);
            }
        }
    }

    int Q;
    cin >> Q;
    vector<int> X(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> X[i];
        if (sum.contains(X[i]))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}