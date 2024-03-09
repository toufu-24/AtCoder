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
    list<int> A;
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        A.push_back(a);
    }
    int Q;
    cin >> Q;
    while (Q--)
    {
        int q;
        cin >> q;
        int x, y;
        int idx_x;
        switch (q)
        {
        case 1:
            cin >> x >> y;
            auto it = find(all(A), x);
            A.insert(++it, y);
            break;
        case 2:
            cin >> x;
            A.remove(x);
            break;
        }
    }
}