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

ld temperture(ld new_score, ld old_score, ld t)
{
    if (t == 0)
    {
        return 0;
    }
    return exp((new_score - old_score) / t);
}

int main()
{
    ld start = clock() / CLOCKS_PER_SEC;
    int N, D;
    cin >> N >> D;
    vector<int> W(N);
    for (int i = 0; i < N; i++)
    {
        cin >> W[i];
    }

    vector<vector<int>> bag(D);
    ld ans = 1e18;
    ld ave = accumulate(all(W), 0) / (ld)D;
    // 初期状態を決める
    for (int i = 0; i < N; i++)
    {
        bag[i % D].push_back(W[i]);
    }
    int cnt = 0;
    ld old_score = 1e18;
    do
    {
        cnt++;
        // 現在の状態から次の状態を決める
        vector<vector<int>> next_bag = bag;
        int i = rand() % D;
        int j = rand() % D;
        if (next_bag[i].size() == 0)
        {
            continue;
        }
        int change = next_bag[i][rand() % next_bag[i].size()];
        next_bag[i].erase(find(all(next_bag[i]), change));
        next_bag[j].push_back(change);

        // 次の状態の評価
        ld new_score = 0;
        vector<ld> sum(D, 0);
        for (int i = 0; i < D; i++)
        {
            sum[i] = accumulate(all(next_bag[i]), 0);
        }
        for (int i = 0; i < D; i++)
        {
            new_score += sum[i] * sum[i];
        }
        new_score /= D;
        new_score -= ave * ave;

        // 次の状態を採用するかどうかを決める
        if (new_score < old_score)
        {
            bag = next_bag;
            old_score = new_score;
            ans = min(ans, new_score);
        }
        else
        {
            ld t = 2 - ((ld)(clock()) / CLOCKS_PER_SEC - start);
            ld p = temperture(new_score, old_score, t);
            if (p > (ld)rand() / RAND_MAX)
            {
                bag = next_bag;
                old_score = new_score;
                ans = min(ans, new_score);
            }
        }
    } while (((ld)(clock()) / CLOCKS_PER_SEC) - start < 1.9);
    cout << fixed << setprecision(10) << ans << endl;
    cerr << cnt << endl;
}