#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<string> ans(powl(3, N), string(powl(3, N), '#'));
    auto f = [&](auto &&f, pair<int, int> left_up, pair<int, int> right_down, int level) -> void
    {
        if (level == 0)
        {
            return;
        }
        int center_left_up_x = (right_down.first - left_up.first) / 3 + left_up.first;
        int center_left_up_y = (right_down.second - left_up.second) / 3 + left_up.second;
        int center_right_down_x = (right_down.first - left_up.first) * 2 / 3 + left_up.first;
        int center_right_down_y = (right_down.second - left_up.second) * 2 / 3 + left_up.second;
        for (int i = center_left_up_x; i < center_right_down_x; i++)
        {
            for (int j = center_left_up_y; j < center_right_down_y; j++)
            {
                ans[i][j] = '.';
            }
        }
        // 左上
        f(f, {left_up.first, left_up.second}, {center_left_up_x, center_left_up_y}, level - 1);
        // 中央上
        f(f, {center_left_up_x, left_up.second}, {center_right_down_x, center_left_up_y}, level - 1);
        // 右上
        f(f, {center_right_down_x, left_up.second}, {right_down.first, center_left_up_y}, level - 1);
        // 左中央
        f(f, {left_up.first, center_left_up_y}, {center_left_up_x, center_right_down_y}, level - 1);
        // 右中央
        f(f, {center_right_down_x, center_left_up_y}, {right_down.first, center_right_down_y}, level - 1);
        // 左下
        f(f, {left_up.first, center_right_down_y}, {center_left_up_x, right_down.second}, level - 1);
        // 中央下
        f(f, {center_left_up_x, center_right_down_y}, {center_right_down_x, right_down.second}, level - 1);
        // 右下
        f(f, {center_right_down_x, center_right_down_y}, {right_down.first, right_down.second}, level - 1);
    };
    f(f, {0, 0}, {powl(3, N), powl(3, N)}, N);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j];
        }
        cout << endl;
    }
}
