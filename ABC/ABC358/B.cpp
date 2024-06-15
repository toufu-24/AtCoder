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
    int N, A;
    cin >> N >> A;
    vector<int> T(N);
    for (int i = 0; i < N; i++)
    {
        cin >> T[i];
    }

    int t_idx = 0;
    int next = 0;
    for (int i = 0; i <= 1e8 + 100; i++)
    {
        if (next <= i)
        {
            if (T[t_idx] <= i)
            {
                t_idx++;
                next = i;
                next += A;
                cout << next << endl;
            }
        }
        if (t_idx == N)
            break;
    }
}
