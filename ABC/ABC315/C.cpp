#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    // フレーバー、おいしさ
    map<int, vector<int>> ice_st;
    vector<int> flavor(N);
    vector<int> delicious(N);
    vector<pair<int, int>> ice;
    for (int i = 0; i < N; i++)
    {
        cin >> flavor[i] >> delicious[i];
        if (ice_st[flavor[i]].size() < 2)
        {
            ice_st[flavor[i]].push_back(delicious[i]);
            ice.push_back(make_pair(flavor[i], delicious[i]));
        }
        else if (ice_st[flavor[i]][0] < delicious[i])
        {
            ice_st[flavor[i]][0] = delicious[i];
            ice.push_back(make_pair(flavor[i], delicious[i]));
        }
        else if (ice_st[flavor[i]][1] < delicious[i])
        {
            ice_st[flavor[i]][1] = delicious[i];
            ice.push_back(make_pair(flavor[i], delicious[i]));
        }
    }
    sort(ice);
    reverse(ice);
    int maximum = 0;
    for (int i = 0; i < ice.size(); i++)
    {
        for (int j = i + 1; j < ice.size(); j++)
        {
            int manzokudo = 0;
            if (ice[i].first == ice[j].first)
            {
                manzokudo = ice[i].second + ice[j].second / 2;
            }
            else
            {
                manzokudo = ice[i].second + ice[j].second;
            }
            maximum = max(maximum, manzokudo);
        }
    }
    cout << maximum << endl;
}