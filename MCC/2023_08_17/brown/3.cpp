#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, D;
    cin >> N >> D;
    vector<pair<int, int>> human(N);
    for (int i = 0; i < N; i++)
    {
        cin >> human[i].first >> human[i].second;
    }
    vector<vector<int>> neighber(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int x = human[i].first - human[j].first;
            int y = human[i].second - human[j].second;
            if (x * x + y * y <= D * D)
            {
                neighber[i].push_back(j);
                neighber[j].push_back(i);
            }
        }
    }
    vector<bool> isInfected(N, false);
    isInfected[0] = true;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (auto next : neighber[now])
        {
            if (!isInfected[next])
            {
                isInfected[next] = true;
                q.push(next);
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (isInfected[i])
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}