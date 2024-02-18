#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> C(N - 1);
    vector<int> S(N - 1);
    vector<int> F(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> C[i] >> S[i] >> F[i];
    }
    for (int station = 0; station < N; station++)
    {
        int now = 0;
        for (int i = station; i < N - 1; i++)
        {
            if (now > S[i])
            {
                // now = S[i] + F[i] * n;
                // now以上になるnの最小値
                int left = -1, right = 1e15;
                while (right - left > 1)
                {
                    int mid = (left + right) / 2;
                    if (now <= S[i] + F[i] * mid)
                    {
                        right = mid;
                    }
                    else
                    {
                        left = mid;
                    }
                }
                now = S[i] + F[i] * right;
            }
            else
            {
                now = S[i];
            }
            now += C[i];
        }
        cout << now << endl;
    }
}