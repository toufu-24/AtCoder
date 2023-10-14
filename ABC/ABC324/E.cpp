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

signed main()
{
    int N;
    cin >> N;
    string T;
    cin >> T;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    vector<int> S_front(N);
    vector<int> S_back(N);
    for (int i = 0; i < N; i++)
    {
        int front_idx = 0;
        int back_idx = T.size() - 1;
        for (int j = 0; j < S[i].size(); j++)
        {
            if (S[i][j] == T[front_idx])
            {
                front_idx++;
            }
            if (S[i][S[i].size() - 1 - j] == T[back_idx])
            {
                back_idx--;
            }
        }
        S_front[i] = front_idx - 1;
        S_back[i] = back_idx + 1;
    }
    SORT(S_front);
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(S_front), S_back[i] - 1) - S_front.begin();
        cnt += N - idx;
    }
    cout << cnt << endl;
}