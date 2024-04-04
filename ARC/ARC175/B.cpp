#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N, A, B;
    cin >> N >> A >> B;
    string S;
    cin >> S;

    stack<int> open_index, close_index;
    for (int i = 0; i < 2 * N; i++)
    {
        if (S[i] == ')')
        {
            if (open_index.empty())
            {
                close_index.push(i);
            }
            else
            {
                open_index.pop();
            }
        }
        else
        {
            open_index.push(i);
        }
    }

    int ans1 = 0, ans2 = 0;
    int ans = 0;

    if (A < B)
    {
        int how_many = close_index.size() / 2;
        ans += A * how_many;
        how_many = max(open_index.size(), close_index.size()) - min(open_index.size(), close_index.size());
        ans += B * how_many / 2;
    }
    else
    {
        ans = B * ((open_index.size() + 1) / 2 + (close_index.size() + 1) / 2);
    }
    cout << ans << endl;
}
