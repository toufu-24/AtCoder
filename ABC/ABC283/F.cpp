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
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    for (int i = 0; i < N; i++)
    {
        unsigned int ans = 2147483647;
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                unsigned int tmp = abs(P[i] - P[j]) + abs(i - j);
                if (tmp < ans)
                {
                    ans = tmp;
                }
            }
        }
        cout << ans << " ";
    }
}