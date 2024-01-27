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

    vector<int> Q_ori = Q;
    int ans = 0;
    // まず，Aの料理をできる限り作る
    int meal_num = 1e9;
    for (int i = 0; i < N; i++)
    {
        meal_num = min(meal_num, Q[i] / A[i]);
    }
    for (int i = 0; i < N; i++)
    {
        Q[i] -= meal_num * A[i];
    }
    ans += meal_num;
    // 次に，Bの料理をできる限り作る
    meal_num = 1e9;
    for (int i = 0; i < N; i++)
    {
        meal_num = min(meal_num, Q[i] / B[i]);
    }
    ans += meal_num;

    // Bの料理をできる限り作る
    int ans2 = 0;
    meal_num = 1e9;
    Q = Q_ori;
    for (int i = 0; i < N; i++)
    {
        meal_num = min(meal_num, Q[i] / B[i]);
    }
    for (int i = 0; i < N; i++)
    {
        Q[i] -= meal_num * B[i];
    }
    ans2 += meal_num;
    // 次に，Aの料理をできる限り作る
    meal_num = 1e9;
    for (int i = 0; i < N; i++)
    {
        meal_num = min(meal_num, Q[i] / A[i]);
    }
    ans2 += meal_num;

    cout << max(ans, ans2) << endl;
}