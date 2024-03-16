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

#define int ll

struct ball
{
    int color;
    int value;
};

int32_t main()
{
    int N, K;
    cin >> N >> K;
    vector<int> C(N);
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i] >> V[i];
    }
    // Cが連続してる中のVの最大値を取る
    vector<int> good_idx;
    vector<int> good;
    int now_c = C[0];
    int now_max_v = V[0];
    int now_max_v_idx = 0;
    for (int i = 1; i < N; i++)
    {
        if (C[i] == now_c)
        {
            if (V[i] > now_max_v)
            {
                now_max_v = V[i];
                now_max_v_idx = i;
            }
            K--;
        }
        else
        {
            good_idx.push_back(now_max_v_idx);
            good.push_back(now_max_v);
            now_c = C[i];
            now_max_v = V[i];
            now_max_v_idx = i;
        }
    }
    good_idx.push_back(now_max_v_idx);
    good.push_back(now_max_v);
    if (K < 0)
    {
        cout << -1 << endl;
        return 0;
    }
    // --------------------これで既に連続してるやつは取った-----------------------
    int remain = good.size() - K;
    vector<pair<int, int>> sorted_good(remain);
    for (int i = 0; i < remain; i++)
    {
        sorted_good[i] = {good[i], good_idx[i]};
    }
    RSORT(sorted_good);
    vector<int> ans_idx;
    for (int i = 0; i < remain; i++)
    {
        ans_idx.push_back(sorted_good[i].second);
    }
    SORT(ans_idx);
    vector<ball> ans;
    for (int i = 0; i < ans_idx.size(); i++)
    {
        ans.push_back({C[ans_idx[i]], V[ans_idx[i]]});
    }
}