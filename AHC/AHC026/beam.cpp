// 小さいものが上に来るようにしたいよね

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long doubles

constexpr int MAX_ORDER = 5000;
constexpr int N = 200;
constexpr int M = 10;
constexpr int nDm = 20;
constexpr int BEAM_WIDTH = 1300;
vector<vector<int>> b(M, vector<int>(nDm));

vector<vector<int>> read_input(int n, int m)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < nDm; j++)
        {
            cin >> b[i][j];
        }
    }
    return b;
}

pair<int, int> find_position(int i, const vector<vector<int>> &b)
{
    int x, y;
    for (int j = 0; j < b.size(); j++)
    {
        for (int k = 0; k < b[j].size(); k++)
        {
            if (b[j][k] == i)
            {
                x = j;
                y = k;
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

vector<int> take_above(int x, int y, vector<vector<int>> &b)
{
    vector<int> above;
    for (int j = y + 1; j < b[x].size(); j++)
    {
        above.push_back(b[x][j]);
    }
    for (int j = 0; j < above.size(); j++)
    {
        b[x].pop_back();
    }
    return above;
}

// 移動先を探す
vector<int> find_move_index(int x, const vector<vector<int>> &b, int size)
{
    vector<tuple<int, int>> scores;
    for (int j = 0; j < b.size(); j++)
    {
        scores.push_back({b[j].size(), j});
    }
    SORT(scores);
    vector<int> ans;
    for (int i = 0; i < min(size, (int)scores.size()); i++)
    {
        if (get<1>(scores[i]) == x)
            continue;
        ans.push_back(get<1>(scores[i]));
    }
    return ans;
}

// 現在の状態の評価値を返す関数
// 小さい方が良い
int evaluate(const vector<vector<int>> &b, int now, int goIdx, int box_size)
{
    int score = 0;
    score += box_size + b[goIdx].size();
    return score + 1;
}

// score, ans, state
vector<tuple<int, vector<pair<int, int>>, vector<vector<int>>>> states;
void beam_search(int n, int m, int beam_width)
{
    b = read_input(n, m);
    states.push_back({0, {}, b});
    for (int i = 1; i <= n; i++)
    {
        vector<tuple<int, vector<pair<int, int>>, vector<vector<int>>>> next_states;
        for (auto [score, ans, state] : states)
        {
            auto [x, y] = find_position(i, state);
            if (y == state[x].size() - 1)
            {
                // assert(state[x][state[x].size() - 1] == i);
                //  取り出すものを出力
                ans.push_back({i, 0});
                // 取り出す
                state[x].pop_back();
                next_states.push_back({score, ans, state});
                ans.pop_back();
            }
            else
            {
                auto above = take_above(x, y, state);
                REVERSE(above);
                auto origin_state = state;
                vector<int> remove;
                for (auto a : above)
                {
                    remove.push_back(a);
                }
                REVERSE(remove);
                auto Index = find_move_index(x, state, M / 3);
                for (int j = 0; j < Index.size(); j++)
                {
                    state = origin_state;
                    for (int k = 0; k < remove.size(); k++)
                    {
                        state[Index[j]].push_back(remove[k]);
                    }
                    // 移動するものを出力
                    ans.push_back({remove[0], Index[j] + 1});
                    // assert(state[x][state[x].size() - 1] == i);
                    //  取り出すものを出力
                    ans.push_back({i, 0});
                    // 取り出す
                    state[x].pop_back();
                    next_states.push_back({score + evaluate(state, i, Index[j], remove.size()), ans, state});
                    ans.pop_back();
                    ans.pop_back();
                }
            }
        }
        SORT(next_states);
        states.clear();
        for (int j = 0; j < min(beam_width, (int)next_states.size()); j++)
        {
            states.push_back(next_states[j]);
        }
    }
}

signed main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    time_t start = clock();
    int _n, _m;
    cin >> _n >> _m;
    int beam_width = BEAM_WIDTH;
    beam_search(N, M, beam_width);
    for (auto [i, j] : get<1>(states[0]))
    {
        cout << i << " " << j << '\n';
    }
    time_t end = clock();
    cerr << "time: " << (double)(end - start) / CLOCKS_PER_SEC << " sec.\n";
    return 0;
}