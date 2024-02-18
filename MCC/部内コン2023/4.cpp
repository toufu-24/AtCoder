// 招待状を送るのは同時か順番があるのかどちらですか？
// 例えば人1,2,3に招待状を送るとき，人2に送る名簿には[人1,人2,人3]と書かれているのか[人1,人2]と書かれているのかどちらですか？

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> dislike(N + M);
    for (int i = 0; i < N + M; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int a;
            cin >> a;
            a--;
            dislike[i].push_back(a);
        }
    }

    vector<int> dp(1 << (N + M), 0);
    int maximum = 0;
    // O(2^(N+M) * (N+M)^2)
    for (int bit = 0; bit < (1 << (N + M)); bit++)
    {
        bool out = false;
        for (int i = 0; i < N + M; i++)
        {
            if (bit & (1 << i))
            {
                for (auto x : dislike[i])
                {
                    if (bit & (1 << x))
                    {
                        out = true;
                        break;
                    }
                }
            }
        }
        if (!out)
        {
            maximum = max(maximum, __builtin_popcount(bit));
        }
    }
    cout << maximum << endl;
}