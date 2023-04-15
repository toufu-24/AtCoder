#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    vector<int> L(Q);
    vector<int> R(Q);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < Q; i++)
    {
        cin >> L[i] >> R[i];
    }
    vector<int> sum(N);
    sum[0] = A[0];
    for (int i = 1; i < N; i++)
    {
        sum[i] = sum[i - 1] + A[i];
    }
    for (int i = 0; i < Q; i++)
    {
        int r = R[i] - 1;
        int l = L[i] - 1;
        cout << sum[R[i] - 1] - sum[L[i] - 2] << endl;
    }
}