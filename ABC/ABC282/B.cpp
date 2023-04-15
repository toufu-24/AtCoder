#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    vector<bitset<30>> S2(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < M; j++)
        {
            if (S[i][j] == 'o')
            {
                S2[i].set(j, 1);
            }
            else
            {
                S2[i].set(j, 0);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            bitset<30> judge;
            judge = S2[i] | S2[j];
            if (judge.count() == M)
            {
                cnt++;
            }
        }
    }
    cout << cnt;
}