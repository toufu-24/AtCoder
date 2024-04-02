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
    int N, X;
    cin >> N >> X;
    vector<int> P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    for (int i = 0; i < N; i++)
    {
        if (P[i] == X)
        {
            cout << i + 1 << endl;
        }
    }
}
