#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(2 * N);
    for (int i = 0; i < 2 * N; i++)
    {
        cin >> A[i];
    }

    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        bool flag = false;
        int prev = -1;
        for (int j = 0; j < 2 * N; j++)
        {
            if (i == A[j])
            {
                if (flag)
                {
                    if (j - prev == 2)
                    {
                        ans++;
                    }
                }
                flag = true;
                prev = j;
            }
        }
    }
    cout << ans;
}
