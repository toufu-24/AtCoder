#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> P(N);
    vector<int> Q(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        Q[i] = P[i];
    }
    for (int i = 0; i < N - 1; i++)
    {
        if (P[i - 1] + 1 != P[i])
        {
            bool s_flag = true;
            for (int j = i + 1; j < N; j++)
            {
                //ソートかどうか
                if (P[j] + 1 != P[j + 1])
                {
                    s_flag = false;
                    break;
                }
            }
            if (!s_flag)
            {
                for (int j = i + 2; j < N; j++)
                {
                    if (P[j] + 1 != P[j + 1])
                    {
                        s_flag = false;
                        break;
                    }
                }

                swap(Q[N - 1], Q[N - 2]);
            }
        }
    }
}