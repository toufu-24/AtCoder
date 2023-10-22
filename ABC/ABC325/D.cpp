// 誤読していた！！！！！

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
// 座標圧縮
// https://ei1333.github.io/luzhiled/snippets/other/compress.htmlより
template <typename T>
struct Compress
{
    vector<T> xs;

    Compress() = default;

    Compress(const vector<T> &vs)
    {
        add(vs);
    }

    Compress(const initializer_list<vector<T>> &vs)
    {
        for (auto &p : vs)
            add(p);
    }

    void add(const vector<T> &vs)
    {
        copy(begin(vs), end(vs), back_inserter(xs));
    }

    void add(const T &x)
    {
        xs.emplace_back(x);
    }

    void build()
    {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
    }

    vector<int> get(const vector<T> &vs) const
    {
        vector<int> ret;
        transform(begin(vs), end(vs), back_inserter(ret), [&](const T &x)
                  { return lower_bound(begin(xs), end(xs), x) - begin(xs); });
        return ret;
    }

    int get(const T &x) const
    {
        return lower_bound(begin(xs), end(xs), x) - begin(xs);
    }

    const T &operator[](int k) const
    {
        return xs[k];
    }
};

signed main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> time(N);
    for (int i = 0; i < N; i++)
    {
        int T, D;
        cin >> T >> D;
        time[i] = make_pair(T, D);
    }
    vector<int> comp;
    for (int i = 0; i < N; i++)
    {
        comp.push_back(time[i].first);
        comp.push_back(time[i].second);
    }
    Compress<int> c(comp);
    c.build();
    vector<int> T(N), D(N);
    for (int i = 0; i < N; i++)
    {
        T[i] = c.get(time[i].first);
        D[i] = c.get(time[i].second) + 1;
    }

    int max_time = max(*max_element(all(D)), *max_element(all(T)));
    vector<int> cnt(max_time + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cnt[T[i]]++;
        cnt[D[i]]--;
    }
    for (int i = 0; i < max_time; i++)
    {
        cnt[i + 1] += cnt[i];
    }

    // dp[i][j] := i時刻までで何枚できるか．j=0ならば印字．j=1ならば印字しない．
    set<int> isPrinted;
    vector<vector<int>> dp(max_time, vector<int>(2, 0));
    dp[0][0] = cnt[0];
    dp[0][1] = 0;
    for (int i = 1; i < max_time; i++)
    {
        if (isPrinted.count())
        {
        }
        dp[i][0] = dp[i - 1][1] + cnt[i];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
    }
    cout << max(dp[max_time - 1][0], dp[max_time - 1][1]) << endl;
}