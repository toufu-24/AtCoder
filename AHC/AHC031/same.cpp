// 等分割することを考える

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
#define chmax(a, b) a = max(a, b)
#define int ll

constexpr int W = 1000;
int D, N;
vector<vector<int>> a;
const vector<int> thousand_divisor = {1, 2, 5, 10, 20, 25, 50, 100, 125, 250, 500, 1000};

void input()
{
    int _;
    cin >> _ >> D >> N;
    a.resize(D, vector<int>(N));
    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> a[i][j];
        }
    }
}

int32_t main()
{
    input();
    int one_area = W * W / (N);
    int one_side = sqrtl(one_area);
    one_side = *prev(lower_bound(all(thousand_divisor), one_side));
    vector<vector<bool>> grid(W, vector<bool>(W, false));
    vector<pair<pair<int, int>, pair<int, int>>> ans;
    pair<int, int> left_up = {0, 0};
    pair<int, int> right_down = {one_side, one_side};
    for (int i = 0; i < N; i++)
    {
        ans.push_back({left_up, right_down});
        left_up.first += one_side;
        right_down.first += one_side;
        if (right_down.first > W)
        {
            left_up.first = 0;
            right_down.first = one_side;
            left_up.second += one_side;
            right_down.second += one_side;
        }
    }
    for (int d = 0; d < D; d++)
    {
        for (auto [l, r] : ans)
        {
            cout << l.first << " " << l.second << " " << r.first << " " << r.second << endl;
        }
    }
}
