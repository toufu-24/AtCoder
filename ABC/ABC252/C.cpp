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
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    int ans = 1e9;
    for (int i = 0; i < 10; i++)
    {
        char c = '0' + i;
        int now_time = 0;
        set<int> already;
        while (true)
        {
            if (already.size() == N)
            {
                break;
            }
            for (int j = 0; j < N; j++)
            {
                if (already.count(j))
                    continue;
                if (S[j][now_time % 10] == c)
                {
                    already.insert(j);
                    break;
                }
            }
            now_time++;
        }
        ans = min(ans, now_time);
    }
    cout << ans - 1 << endl;
}