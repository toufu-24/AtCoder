#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, D;
    cin >> N >> D;
    vector<pair<int, int>> human(N);
    vector<bool> flag(N, false);
    for (int i = 0; i < N; i++)
    {
        int X, Y;
        cin >> X >> Y;
        human[i] = make_pair(X, Y);
    }
    flag[0] = true;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int virus = q.front();
        q.pop();
        for (int i = 0; i < N; i++)
        {
            if (flag[i])
            {
                continue;
            }
            int X = human[i].first;
            int Y = human[i].second;
            if (sqrt(pow((human[virus].first - X), 2) + pow((human[virus].second - Y), 2)) <= D)
            {
                flag[i] = true;
                q.push(i);
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << (flag[i] ? "Yes" : "No") << endl;
    }
}