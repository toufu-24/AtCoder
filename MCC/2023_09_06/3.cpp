#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
// #define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> town(N);
    vector<int> x(N);
    vector<int> y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> x[i] >> y[i];
        town[i] = make_pair(x[i], y[i]);
    }
    set<pair<int, int>> ans;
    for (int i = 0; i < N; i++)
    {
        int nx = x[i];
        int ny = y[i];
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;
            int mx = x[j];
            int my = y[j];
            int dx = mx - nx;
            int dy = my - ny;
            // dx，dyを互いに素にする
            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;
            ans.insert(make_pair(dx, dy));
        }
    }
    cout << ans.size() << endl;
}