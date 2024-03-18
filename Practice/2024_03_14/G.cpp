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
    int N, X;
    cin >> N >> X;
    string S;
    cin >> S;
    // "LU"，"RU"は無駄
    stack<int> LR_idx;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'L' || S[i] == 'R')
        {
            LR_idx.push(i);
        }
        else
        {
            if (LR_idx.empty())
            {
                continue;
            }
            int idx = LR_idx.top();
            LR_idx.pop();
            S[idx] = 'X';
            S[i] = 'X';
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'L')
        {
            X = 2 * X;
        }
        else if (S[i] == 'R')
        {
            X = 2 * X + 1;
        }
        else if (S[i] == 'U')
        {
            X = X / 2;
        }
    }
    cout << X << endl;
}