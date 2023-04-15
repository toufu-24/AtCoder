#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, L, K;
    cin >> N >> L >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> score(K + 1, 0);
    vector<int> length(N + 1);
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        length[i] = A[i] - sum;
        sum += length[i];
    }
    length[N] = L - sum;
    double reference = double(L) / double(K + 1);
    int j = 0;
    for (int i = 0; i <= K; i++)
    {
        for (; j < N + 1; j++)
        {
            score[i] += length[j];
            if (score[i] >= reference)
            {
                if (abs(score[i] - length[j] - reference) <= abs(score[i] - reference))
                {
                    score[i] -= length[j];
                }
                else
                {
                    j++;
                }
                break;
            }
        }
    }
    sort(score.begin(), score.end());
    cout << score[0] << endl;
}