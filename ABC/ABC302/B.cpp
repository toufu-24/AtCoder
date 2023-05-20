#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int H, W;
vector<pair<int, int>> ans(5);

bool go(vector<vector<char>> S, pair<int, int> second)
{
    if (second != make_pair(-1, -1))
    {
        int horizontal = second.second - ans[0].second;
        int vertical = second.first - ans[0].first;
        if ((second.first + vertical >= 0) && (second.second + horizontal >= 0) && (second.first + vertical <= H - 1) && (second.second + horizontal <= W - 1) && S[second.first + vertical][second.second + horizontal] == 'u')
        {
            if ((second.first + vertical * 2 >= 0) && (second.second + horizontal * 2 >= 0) && !(second.first + vertical * 2 > H - 1) && !(second.second + horizontal * 2 > W - 1) && S[second.first + vertical * 2][second.second + horizontal * 2] == 'k')
            {
                if ((second.first + vertical * 3 >= 0) && (second.second + horizontal * 3 >= 0) && !(second.first + vertical * 3 > H - 1) && !(second.second + horizontal * 3 > W - 1) && S[second.first + vertical * 3][second.second + horizontal * 3] == 'e')
                {
                    ans[1] = second;
                    ans[2] = make_pair(second.first + vertical, second.second + horizontal);
                    ans[3] = make_pair(second.first + vertical * 2, second.second + horizontal * 2);
                    ans[4] = make_pair(second.first + vertical * 3, second.second + horizontal * 3);
                    return true;
                }
            }
        }
    }
    return false;
}

bool search(vector<vector<char>> S, pair<int, int> now, char target)
{
    if (now.first != H - 1 && S[now.first + 1][now.second] == target && go(S, make_pair(now.first + 1, now.second)))
    {
        return true;
    }
    else if (now.second != W - 1 && S[now.first][now.second + 1] == target && go(S, make_pair(now.first, now.second + 1)))
        return true;
    else if (now.first != 0 && S[now.first - 1][now.second] == target && go(S, make_pair(now.first - 1, now.second)))
        return true;
    else if (now.second != 0 && S[now.first][now.second - 1] == target && go(S, make_pair(now.first, now.second - 1)))
        return true;
    else if (now.first != H - 1 && now.second != W - 1 && S[now.first + 1][now.second + 1] == target && go(S, make_pair(now.first + 1, now.second + 1)))
        return true;
    else if (now.first != H - 1 && now.second != 0 && S[now.first + 1][now.second - 1] == target && go(S, make_pair(now.first + 1, now.second - 1)))
        return true;
    else if (now.first != 0 && now.second != W - 1 && S[now.first - 1][now.second + 1] == target && go(S, make_pair(now.first - 1, now.second + 1)))
        return true;
    else if (now.first != 0 && now.second != 0 && S[now.first - 1][now.second - 1] == target && go(S, make_pair(now.first - 1, now.second - 1)))
        return true;
    else
        return false;
}

int main()
{
    cin >> H >> W;
    vector<vector<char>> S(H, vector<char>(W));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            cin >> S[i][j];
    bool ans_flag = false;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (S[i][j] == 's')
            {
                ans[0] = make_pair(i, j);
                if (search(S, ans[0], 'n'))
                {
                    ans_flag = true;
                    break;
                }
            }
        }
        if (ans_flag)
            break;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }
}