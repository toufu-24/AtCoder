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
    pair<int, int> most_delicious_ice;
    int most_delicious = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> flavor[i] >> delicious[i];
        ice.push_back(make_pair(flavor[i], delicious[i]));
        if (most_delicious_ice.second < delicious[i])
        {
            most_delicious_ice = make_pair(flavor[i], delicious[i]);
            most_delicious = i;
        }
    }
    int maximum = 0;
    for (int i = 0; i < N; i++)
    {
        if (i == most_delicious)
            continue;
        int manzokudo = 0;
        if (most_delicious_ice.first == ice[i].first)
        {
            manzokudo = most_delicious_ice.second + ice[i].second / 2;
        }
        else
        {
            manzokudo = most_delicious_ice.second + ice[i].second;
        }
        maximum = max(maximum, manzokudo);
    }
    cout << maximum << endl;
}