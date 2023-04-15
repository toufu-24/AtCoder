#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int64_t N;
    cin >> N;
    int64_t Q;
    cin >> Q;
    vector<int64_t> tmp(N);
    for (int64_t i = 0; i < N; i++)
    {
        cin >> tmp[i];
    }
    vector<int64_t> q_num(Q);
    vector<int64_t> q_x(Q, 0);
    vector<int64_t> q_i(Q, 0);
    int count_1 = 0;
    for (int64_t i = 0; i < Q; i++)
    {
        cin >> q_num[i];
        if (q_num[i] == 1)
        {
            cin >> q_x[i];
            count_1++;
        }
        else if (q_num[i] == 2)
        {
            cin >> q_i[i] >> q_x[i];
        }
        else if (q_num[i] == 3)
        {
            cin >> q_i[i];
        }
    }
    vector<vector<int64_t>> A(N, vector<int64_t>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = j;
        }
    }

    for (int64_t i = 0; i < N; i++)
    {
        cin >> A[0][i];
    }
    int cnt = 0;
    for (int64_t i = 0; i < Q; i++)
    {
        if (q_num[i] == 1)
        {
            cnt = q_x[i];
        }
        else if (q_num[i] == 2)
        {
            A[cnt][q_i[i] - 1] += q_x[i];
        }
        else if (q_num[i] == 3)
        {
            cout << A[cnt][q_i[i] - 1] << endl;
        }
    }
}