#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int sum[A[N - 1] + 1] ={};

    int A_index = 1;
    bool plus = false;
    for (int i = 0; i < A[N - 1]; i++)
    {
        if (i != 0 && A_index < N && i == A[A_index])
        {
            plus = !plus;
            A_index++;
        }
        if (plus)
        {
            sum[i + 1] = sum[i] + 1;
        }
        else
        {
            sum[i + 1] = sum[i];
        }
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << sum[r] - sum[l] << endl;
    }
}