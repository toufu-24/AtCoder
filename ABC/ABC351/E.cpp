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
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i] >> Y[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            // 差の和が偶数なら移動可能
            int sa = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
            if (sa % 2 == 0)
            {
                ans += sa / 2;
            }
        }
    }
    cout << ans << endl;
}
