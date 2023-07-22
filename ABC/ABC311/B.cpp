#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, D;
    cin >> N >> D;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
        cin >> S[i];

    int maximum = 0;
    // すべての日にちについて
    for (int i = 0; i < D; i++)
    {
        int count = 0;
        bool flag = true;
        // 日からあと
        for (int j = i; j < D; j++)
        {
            // すべての人について
            for (int k = 0; k < N; k++)
            {
                if (S[k][j] == 'x')
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                count++;
            else
                break;
        }
        maximum = max(maximum, count);
    }

    cout << maximum;
}