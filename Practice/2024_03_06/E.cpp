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
    vector<int> ball(N);
    iota(all(ball), 0);
    vector<int> idx(N);
    iota(all(idx), 0);

    while (Q--)
    {
        int x;
        cin >> x;
        x--;
        int x_idx = idx[x];
        int right_idx = x_idx + 1;
        if (right_idx == N)
        {
            right_idx = N - 2;
        }
        int right = ball[right_idx];
        idx[x] = right_idx;
        idx[right] = x_idx;
        swap(ball[x_idx], ball[right_idx]);
    }

    for (int i = 0; i < N; i++)
    {
        cout << ball[i] + 1 << endl;
    }
}