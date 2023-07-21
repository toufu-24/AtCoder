#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S_tmp(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S_tmp[i];
    }
    vector<string> S(W);
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            S[i] += S_tmp[j][i];
        }
    }
    multiset<string> S_set;
    for (int i = 0; i < W; i++)
    {
        S_set.insert(S[i]);
    }

    vector<string> T_tmp(H);
    for (int i = 0; i < H; i++)
    {
        cin >> T_tmp[i];
    }
    vector<string> T(W);
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            T[i] += T_tmp[j][i];
        }
    }
    for (int i = 0; i < W; i++)
    {
        auto itr = S_set.find(T[i]);
        if (itr == S_set.end())
        {
            cout << "No" << endl;
            return 0;
        }
        else
        {
            S_set.erase(itr);
        }
    }
    cout << "Yes" << endl;
}