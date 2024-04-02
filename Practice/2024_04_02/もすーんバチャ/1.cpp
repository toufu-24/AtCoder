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
    int N, P, Q, R, S;
    cin >> N >> P >> Q >> R >> S;
    P--;
    Q--;
    R--;
    S--;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> PQ;
    for (int i = P; i <= Q; i++)
    {
        PQ.push_back(A[i]);
    }
    vector<int> RS;
    for (int i = R; i <= S; i++)
    {
        RS.push_back(A[i]);
    }
    for (int i = 0; i < N; i++)
    {
        if (i < P)
        {
            cout << A[i] << " ";
        }
        else if (i <= Q)
        {
            cout << RS[i - P] << " ";
        }
        else if (i < R)
        {
            cout << A[i] << " ";
        }
        else if (i <= S)
        {
            cout << PQ[i - R] << " ";
        }
        else
        {
            cout << A[i] << " ";
        }
    }
}
