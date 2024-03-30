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
    vector<int> x(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> x[i];
        x[i]--;
    }
    vector<int> A(N, 0);
    set<int> S;
    for (auto x : x)
    {
        if (S.contains(x))
        {
            S.erase(x);
        }
        else
        {
            S.insert(x);
        }
        for (int i = 0; i < N; i++)
        {
            if (S.count(i))
            {
                A[i] += S.size();
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
}
