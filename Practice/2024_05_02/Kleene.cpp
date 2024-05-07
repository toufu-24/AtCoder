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

using mint = modint1000000007;

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    mint ans = 0;
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        for (int j = i + 1; j < N; j++)
        {
            if (A[i] > A[j])
            {
                cnt++;
            }
        }
        int o_cnt = 0;
        for (int j = 0; j < i; j++)
        {
            if (A[i] > A[j])
            {
                o_cnt++;
            }
        }

        // cnt * K から cnt * 1までの等差数列の和
        mint tmp = K * mint(cnt + mint(cnt) * K) * mint(2).inv();
        ans += tmp;
        // o_cnt * K-1 から o_cnt * 1までの等差数列の和
        tmp = (K - 1) * mint(o_cnt + mint(o_cnt) * (K - 1)) * mint(2).inv();
        ans += tmp;
    }
    cout << ans.val() << endl;
}
