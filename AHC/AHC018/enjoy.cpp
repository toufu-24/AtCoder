#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    // 土地のサイズ
    int LandSize;
    vector<vector<bool>> map(LandSize, vector<bool>(LandSize, false));
    // 水源の数
    int WaterNum;
    // 家の数
    int HouseNum;
    // 消費体力
    int Consume;
    cin >> LandSize >> WaterNum >> HouseNum >> Consume;
    vector<pair<int, int>> water(WaterNum);
    for (int i = 0; i < WaterNum; i++)
    {
        cin >> water[i].first >> water[i].second;
    }
    vector<pair<int, int>> house(HouseNum);
    for (int i = 0; i < HouseNum; i++)
    {
        cin >> house[i].first >> house[i].second;
    }
    bool first_flag = false;
    for (int i = 0; i < LandSize; i++)
    {
        for (int j = 0; j < LandSize; j++)
        {
            int r = 1;
            if (first_flag)
            {
                cin >> r;
            }
            first_flag = true;
            if (r != 0 && r != 1)
            {
                exit(0);
            }
            cout << i << " " << j << " " << 200 << endl;
        }
    }
}