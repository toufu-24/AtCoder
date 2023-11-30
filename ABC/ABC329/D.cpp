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

int op(int a, int b)
{
    if (a == b)
    {
        return a;
    }
    else
    {
        return max(a, b);
    }
}

int e()
{
    return 0;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
        A[i]--;
    }
    map<int, set<int>> mp;
    segtree<int, op, e> seg(N);
    for (int i = 0; i < M; i++)
    {
        int x = seg.get(A[i]);
        mp[x].erase(A[i]);
        seg.set(A[i], x + 1);
        mp[x + 1].insert(A[i]);
        int minimum = seg.all_prod();
        cout << *mp[minimum].begin() + 1 << endl;
    }
}