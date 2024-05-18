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
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
    }
    map<int, vector<int>> front_pairs, back_pairs;
    for (int i = 0; i < N; i++)
    {
        front_pairs[A[i]].push_back(i);
        back_pairs[B[i]].push_back(i);
    }

    // 青木が勝つならtrue
    auto dfs = [&](auto dfs, int turn, vector<bool> &used) -> bool
    {
        // 全ての手を打ったら終了
        if (all_of(all(used), [](bool b)
                   { return b; }))
        {
            return turn == 1; // 終わるときに高橋のターンなら青木の勝ち
        }

        // 青木のターン
        // 青木はどの手でも打てる
        if (turn == 0)
        {
            for (int i = 0; i < N; i++)
            {
                if (used[i])
                {
                    continue;
                }
                used[i] = true;
                for (auto j : front_pairs[A[i]])
                {
                    if (used[j])
                    {
                        continue;
                    }
                    used[j] = true;
                    if (dfs(dfs, turn ^ 1, used))
                    {
                        return true;
                    }
                    used[j] = false;
                }
                for (auto j : back_pairs[B[i]])
                {
                    if (used[j])
                    {
                        continue;
                    }
                    used[j] = true;
                    if (dfs(dfs, turn ^ 1, used))
                    {
                        return true;
                    }
                    used[j] = false;
                }
            }
            return false;
        }
        // 高橋のターン
        // 高橋は勝てる手を打つ
        else
        {
            bool takahashi_win = false;
            for (int i = 0; i < N; i++)
            {
                if (used[i])
                {
                    continue;
                }
                used[i] = true;
                for (auto j : front_pairs[A[i]])
                {
                    if (used[j])
                    {
                        continue;
                    }
                    used[j] = true;
                    takahashi_win |= !dfs(dfs, turn ^ 1, used);
                    used[j] = false;
                }
                for (auto j : back_pairs[B[i]])
                {
                    if (used[j])
                    {
                        continue;
                    }
                    used[j] = true;
                    takahashi_win |= !dfs(dfs, turn ^ 1, used);
                    used[j] = false;
                }
            }
            return !takahashi_win;
        }
    };

    vector<bool> used(N, false);
    for (auto [a, v] : front_pairs)
    {
        auto b_v = back_pairs[a];
        if (b_v.size() == 1 && v.size() == 1 && b_v[0] == v[0])
        {
            used[b_v[0]] = true;
        }
    }

    if (dfs(dfs, 1, used))
    {
        cout << "Aoki" << endl;
    }
    else
    {
        cout << "Takahashi" << endl;
    }
}
