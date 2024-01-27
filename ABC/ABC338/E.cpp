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
    vector<pair<int, int>> point(N);
    for (int i = 0; i < N; i++)
    {
        cin >> point[i].first >> point[i].second;
    }
    SORT(point);

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int a = point[i].first;
            int b = point[i].second;
            int c = point[j].first;
            int d = point[j].second;
            if (judge(a, b, c, d))
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}