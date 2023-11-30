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
    vector<pair<int, int>> people(N);
    for (int i = 0; i < N; i++)
    {
        cin >> people[i].first >> people[i].second;
    }
    string S;
    cin >> S;
    // 0 -> L, 1 -> R
    vector<map<int, vector<int>>> row(2);
    for (int i = 0; i < N; i++)
    {
        int idx = (S[i] == 'L' ? 0 : 1);
        row[idx][people[i].second].push_back(people[i].first);
    }
    for (int i = 0; i < 2; i++)
    {
        for (auto &p : row[i])
        {
            SORT(p.second);
        }
    }
    bool collision = false;
    for (int i = 0; i < N; i++)
    {
        int idx = (S[i] == 'L' ? 0 : 1);
        int y = people[i].second;
        int x = people[i].first;
        // 左に行くとき
        if (idx == 0)
        {
            if (row[1][y].empty())
                continue;
            int min_x = row[1][y][0];
            if (min_x < x)
            {
                collision = true;
                break;
            }
        }
        // 右に行くとき
        else
        {
            if (row[0][y].empty())
                continue;
            int max_x = row[0][y].back();
            if (max_x > x)
            {
                collision = true;
                break;
            }
        }
    }
    if (collision)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}