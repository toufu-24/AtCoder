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
    vector<int> q(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> q[i];
        q[i]--;
    }
    vector<int> A(N, 0);
    set<int> S;
    vector<int> prev_sum(N, -1);
    int sum = 0;
    for (int i = 0; i < Q; i++)
    {
        int x = q[i];
        if (S.contains(x))
        {
            S.erase(x);
            A[x] += sum - prev_sum[x];
            prev_sum[x] = -1;
        }
        else
        {
            S.insert(x);
            prev_sum[x] = sum;
        }
        sum += S.size();
    }
    for (int i = 0; i < N; i++)
    {
        if (prev_sum[i] != -1)
        {
            A[i] += sum - prev_sum[i];
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
}
