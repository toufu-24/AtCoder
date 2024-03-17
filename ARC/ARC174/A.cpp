#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long long
#define ld long double

#define int ll

int32_t main()
{
    int N, C;
    cin >> N >> C;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    if (C > 0)
    {
        // 連続部分列の区間和最大値の区間に適用
        int ans = 0;
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += A[i];
            ans = max(ans, sum);
            sum = max(sum, 0LL);
        }
        cerr << ans << endl;
        cout << reduce(all(A)) + (C - 1) * ans << endl;
    }
    else
    {
        // 連続部分列の区間和最小値の区間に適用
        int ans = 0;
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += A[i];
            ans = min(ans, sum);
            sum = min(sum, 0LL);
        }
        cerr << ans << endl;
        cout << reduce(all(A)) + (C - 1) * ans << endl;
    }
}