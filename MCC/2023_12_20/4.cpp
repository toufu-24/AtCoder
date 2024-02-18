#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int op_max(int a, int b)
{
    return max(a, b);
}

int e()
{
    return 0;
}

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    map<int, set<int>> mp;
    for (int i = 0; i < N; i++)
    {
        mp[A[i]].insert(i);
    }

    int remain = M;
    segtree<int, op_max, e> seg(N);
    for (int i = 0; i < N; i++)
    {
        seg.set(i, A[i]);
    }

    while (remain > 0)
    {
        int max_value = seg.prod(0, N);
        int max_index = *mp[max_value].begin();
        if (remain >= M - max_value)
        {
            seg.set(max_index, 0);
            mp[max_value].erase(max_index);
            A[max_index] = 0;
            remain -= (M - max_value);
        }
        else
        {
            break;
        }
    }
    cout << *max_element(all(A)) << endl;
}