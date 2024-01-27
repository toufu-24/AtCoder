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

bool judge(int a, int b, int c, int d)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);

    return ((a < c && c < b && b < d) || (c < a && a < d && d < b));
}

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].first >> points[i].second;
    }
    SORT(points);

    set<pair<int, int>> active;
    for (int i = 0; i < N; i++)
    {
        auto [a, b] = points[i];
        for (auto it = active.begin(); it != active.end();)
        {
            auto [c, d] = *it;
            if (d <= b)
            {
                it = active.erase(it);
            }
            else
            {
                if (judge(a, b, c, d))
                {
                    cout << "Yes" << endl;
                    return 0;
                }
                it++;
            }
        }
        active.insert({a, b});
    }
    cout << "No" << endl;
}