#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int N, K;
    cin >> N >> K;
    int cnt = 0;
    for (int i = 1; i <= N; i++)
    {
        if (i >= K)
        {
            break;
        }
        for (int j = 1; j <= N; j++)
        {
            if (i + j >= K)
            {
                break;
            }
            if (K - (i + j) >= 1 && K - (i + j) <= N)
            {
                cnt++;
            }
        }
    }
    cout << cnt;
}