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

int main()
{
    int N, Q;
    cin >> N >> Q;
    map<int, int> idx;
    vector<int> ans(N);
    for (int i = 0; i < N; i++)
    {
        idx[i] = i;
        ans[i] = i;
    }
    while (Q--)
    {
        int x;
        cin >> x;
        x--;
        int x_idx = idx[x];
        int x1_idx = x_idx + 1;
        if (x_idx == N - 1)
        {
            x1_idx -= 2;
        }
        idx[ans[x1_idx]] = x_idx;
        idx[x] = x1_idx;
        swap(ans[x_idx], ans[x1_idx]);
    }

    for (auto x : ans)
    {
        cout << x + 1 << " ";
    }
}