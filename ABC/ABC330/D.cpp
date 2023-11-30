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
    int N;
    cin >> N;
    vector<string> S(N);
    vector<pair<int, int>> circle;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'o')
            {
                circle.push_back({i, j});
            }
        }
    }

    // 2個並び
    int ans = 0;
    // 行ごと
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        set<int> idx;
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'o')
            {
                cnt++;
                idx.insert(j);
            }
        }
        if (cnt != 2)
        {
            continue;
        }
        for (auto c : circle)
        {
            if (c.first == i)
            {
                continue;
            }
            if (idx.count(c.second))
            {
                continue;
            }
            ans++;
        }
    }

    // 列ごと
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        set<int> idx;
        for (int j = 0; j < N; j++)
        {
            if (S[j][i] == 'o')
            {
                cnt++;
                idx.insert(j);
            }
        }
        if (cnt != 2)
        {
            continue;
        }
        for (auto c : circle)
        {
            if (c.second == i)
            {
                continue;
            }
            if (idx.count(c.first))
            {
                continue;
            }
            ans++;
        }
    }

    // 3個並び
    // 行ごと
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        set<int> idx;
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'o')
            {
                cnt++;
                idx.insert(j);
            }
        }
        if (cnt != 3)
        {
            continue;
        }
        for (auto c : circle)
        {
            if (c.first == i)
            {
                continue;
            }
            if (idx.count(c.second))
            {
                continue;
            }
            ans++;
        }
    }

    cout << ans << endl;
}
