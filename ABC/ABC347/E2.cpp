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
    vector<int> prev(N, -1);
    for (int i = 0; i < Q; i++)
    {
        int x = q[i];
        if (S.contains(x))
        {
            S.erase(x);
            A[x] += i - prev[x];
            prev[x] = -1;
        }
        else
        {
            S.insert(x);
            prev[x] = i;
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (prev[i] != -1)
        {
            A[i] += N - prev[i];
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
}
