#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

// 連長圧縮
vector<pair<char, int>> runlength(string S)
{
    vector<pair<char, int>> res;
    int cnt = 1;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == S[i + 1])
            cnt++;
        else
        {
            res.push_back(make_pair(S[i], cnt));
            cnt = 1;
        }
    }
    return res;
}

int main()
{
    string S, T;
    cin >> S >> T;
    vector<pair<char, int>> S_run = runlength(S);
    vector<pair<char, int>> T_run = runlength(T);
    if (S_run.size() != T_run.size())
    {
        cout << "No";
        return 0;
    }
    for (int i = 0; i < S_run.size(); i++)
    {
        if (S_run[i].first != T_run[i].first || S_run[i].second > T_run[i].second || (S_run[i].second < 2 && T_run[i].second > S_run[i].second))
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}