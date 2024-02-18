#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0)
        {
            break;
        }
        int base = M / N;
        int64_t sum = 0;
        vector<int> A(N);
        for (int i = 0; i < N; i++)
        {
            cin >> A[i];
            if (A[i] > base)
            {
                sum += base;
            }
            else
            {
                sum += A[i];
            }
        }
        cout << sum << "\n";
    }
}