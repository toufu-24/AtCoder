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
    int N, A, B;
    cin >> N >> A >> B;

    string _S;
    cin >> _S;
    deque<char> S;
    for (int i = 0; i < N; i++)
    {
        S.push_back(_S[i]);
    }

    int ans = numeric_limits<int>::max();
    // A -> Bのみを考えてもよい
    // i回ずらした状態
    for (int i = 0; i <= N + 5; i++)
    {
        // B
        int front_idx = 0;
        int back_idx = S.size() - 1;
        int cnt = 0;
        while (front_idx < back_idx)
        {
            if (S[front_idx] != S[back_idx])
            {
                cnt++;
            }
            front_idx++;
            back_idx--;
        }

        ans = min(ans, i * A + cnt * B);

        S.push_back(S[0]);
        S.pop_front();
    }
    cout << ans << endl;
}