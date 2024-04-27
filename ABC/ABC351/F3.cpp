#pragma GCC optimize("Ofast")

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

int op(int a, int b)
{
    return a + b;
}

int e()
{
    return 0;
}

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    map<int, vector<int>> mp;
    vector<int> sortedA = A;
    SORT(sortedA);
    for (int i = 0; i < N; i++)
    {
        mp[sortedA[i]].push_back(i);
    }
    map<int, int> idx_arr;

    int ans = 0;
    segtree<int, op, e> seg(N);
    segtree<int, op, e> howmany(N);
    for (int i = N - 1; i >= 0; i--)
    {
        // A[i]より大きい要素の個数
        int cnt = howmany.prod(mp[A[i]][idx_arr[A[i]]], N);
        // A[i]より大きい要素の和
        int sum = seg.prod(mp[A[i]][idx_arr[A[i]]], N);
        ans += sum - A[i] * cnt;

        int insertIndex = mp[A[i]][idx_arr[A[i]]];
        idx_arr[A[i]]++;
        seg.set(insertIndex, A[i]);
        howmany.set(insertIndex, 1);
    }
    cout << ans << endl;
}
