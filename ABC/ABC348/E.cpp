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

template <typename T>
struct WeightedUnionFind
{
    vector<int> data;
    vector<T> ws;

    WeightedUnionFind() {}

    WeightedUnionFind(int sz) : data(sz, -1), ws(sz) {}

    int find(int k)
    {
        if (data[k] < 0)
            return k;
        auto par = find(data[k]);
        ws[k] += ws[data[k]];
        return data[k] = par;
    }

    T weight(int t)
    {
        find(t);
        return ws[t];
    }

    bool unite(int x, int y, T w)
    {
        w += weight(x);
        w -= weight(y);
        x = find(x), y = find(y);
        if (x == y)
            return false;
        if (data[x] > data[y])
        {
            swap(x, y);
            w *= -1;
        }
        data[x] += data[y];
        data[y] = x;
        ws[y] = w;
        return true;
    }

    T diff(int x, int y)
    {
        return weight(y) - weight(x);
    }
};

int32_t main()
{
    int N;
    cin >> N;
    vector<vector<int>> G(N);
    vector<int> A(N - 1), B(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> A[i] >> B[i];
        A[i]--;
        B[i]--;
        G[B[i]].push_back(A[i]);
        G[A[i]].push_back(B[i]);
    }
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }

    WeightedUnionFind<int> uf(N);
    for (int i = 0; i < N; i++)
    {
        for (int j : G[i])
        {
            uf.unite(i, j, 1);
        }
    }

    int ans = 1e18;
    for (int i = 0; i < N; i++)
    {
        int tmp = 0;
        for (int j = 0; j < N; j++)
        {
            tmp += abs(uf.diff(i, j)) * C[j];
        }
        ans = min(ans, tmp);
    }
    cout << ans << endl;
}
