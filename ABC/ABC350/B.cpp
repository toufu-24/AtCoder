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
    int N, Q;
    cin >> N >> Q;
    vector<int> T(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> T[i];
    }

    vector<bool> teeth(N, true);
    for (int i = 0; i < Q; i++)
    {
        int x = T[i];
        if (teeth[x - 1])
        {
            teeth[x - 1] = false;
        }
        else
        {
            teeth[x - 1] = true;
        }
    }
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        if (teeth[i])
        {
            sum++;
        }
    }
    cout << sum << endl;
}
