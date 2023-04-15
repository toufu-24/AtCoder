#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<char> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    vector<pair<int, int>> query(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> query[i].first >> query[i].second;
    }
    for (int i = 0; i < Q; i++)
    {
        if (query[i].first == 1)
        {
            for (int k = 0; k < query[k].second; k++)
            {
                char tmp = S[N - 1];
                for (int j = N - 1; j > 0; j--)
                {
                    S[j] = S[j - 1];
                }
                S[0] = tmp;
            }
        }
        else
        {
            cout << S[query[i].second - 1] << endl;
        }
    }
}