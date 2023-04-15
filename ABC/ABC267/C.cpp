#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> sum_num(N - M + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (i >= M - 1)
        {
            for (int j = 0; j < M; j++)
            {
                sum_num[i - M + 1] += (M - j) * A[i - j];
            }
        }
    }

    sort(sum_num.begin(), sum_num.end());
    cout << sum_num[N - M] << endl;
}