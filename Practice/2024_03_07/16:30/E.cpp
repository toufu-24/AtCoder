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
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
    }
    vector<int> point(N, 0);
    vector<pair<int, int>> P_idx;
    vector<string> S;
    for (int i = 0; i < N; i++)
    {
        string S_;
        cin >> S_;
        for (int j = 0; j < S_.size(); j++)
        {
            if (S_[j] == 'o')
            {
                point[i] += A[j];
            }
        }
        point[i] += i + 1;
        S.push_back(S_);
        P_idx.push_back({A[i], i});
    }

    RSORT(P_idx);
    vector<int> ans(N, 0);
    for (int i = 0; i < N; i++)
    {
        int diff = 0;
        int idx = P_idx[i].second;
        bool isTop = true;
        for (int j = 0; j < N; j++)
        {
            if (idx == j)
            {
                continue;
            }
            if (point[j] - point[idx] > diff)
            {
                diff = point[j] - point[idx];
                isTop = false;
            }
        }

        int cnt = 0;
        for (int j = 0; j < M; j++)
        {
            int pro_idx = P_idx[j].second;
            if (diff < 0)
            {
                break;
            }
            if (S[idx][pro_idx] == 'x')
            {
                diff -= P_idx[j].first;
                cnt++;
            }
        }
        ans[idx] = cnt;
        if (isTop)
        {
            ans[idx] = 0;
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << endl;
    }
}