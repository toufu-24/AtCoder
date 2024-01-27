#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> Q(N);
    for (int i = 0; i < N; i++)
    {
        cin >> Q[i];
    }
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }

    int ans = 0;
    // i人分のA料理を作った時に，B料理をドンくらい作れるか
    for (int i = 0; i <= 1e6; i++)
    {
        int minimum = 1e9;
        bool ok = true;
        for (int j = 0; j < N; j++)
        {
            if (Q[j] >= i * A[j])
            {
                if (B[j] != 0)
                    minimum = min(minimum, (Q[j] - i * A[j]) / B[j]);
            }
            else
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            break;
        }
        ans = max(ans, i + minimum);
    }
    cout << ans << endl;
}