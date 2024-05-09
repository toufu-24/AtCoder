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
    int max_A = 0;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        max_A = max(max_A, A[i]);
    }

    dsu d(max_A + 1);
    for (int i = 0; i < N / 2; i++)
    {
        if (A[i] != A[N - 1 - i])
        {
            d.merge(A[i], A[N - 1 - i]);
        }
    }

    // 各連結成分の個数
    int ans = 0;
    auto groups = d.groups();
    for (auto group : groups)
    {
        int size = group.size();
        ans += size - 1;
    }
    cout << ans << endl;
}
