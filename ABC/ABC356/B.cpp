#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
    }
    vector<vector<int>> X(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> X[i][j];
        }
    }
    vector<int> sum(M, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            sum[j] += X[i][j];
        }
    }

    bool ok = true;
    for (int i = 0; i < M; i++)
    {
        if (sum[i] < A[i])
        {
            ok = false;
            break;
        }
    }
    if (ok)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}
