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

using mint = modint998244353;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    vector<int> b(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> b[i];
    }
    vector<mint> a_prefix(N), b_prefix(N);
    set<int> a_set, b_set;
    a_prefix[0] = a[0];
    a_set.insert(a[0]);
    b_prefix[0] = b[0];
    b_set.insert(b[0]);
    for (int i = 1; i < N; i++)
    {
        if (!a_set.count(a[i]))
            a_prefix[i] = a_prefix[i - 1] * a[i];
        else
            a_prefix[i] = a_prefix[i - 1];
        if (!b_set.count(b[i]))
            b_prefix[i] = b_prefix[i - 1] * b[i];
        else
            b_prefix[i] = b_prefix[i - 1];
        a_set.insert(a[i]);
        b_set.insert(b[i]);
    }

    int Q;
    cin >> Q;
    while (Q--)
    {
        int x, y;
        cin >> x >> y;
        if (a_prefix[x - 1] == b_prefix[y - 1])
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}