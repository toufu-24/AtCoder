#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

#define BASEPOWER 100
#define BIGGERPOWER 100
#define howTimesAllow 0
#define houseX(i) house[i].first
#define houseY(i) house[i].second
#define targetAll(i) map[houseX(target)][houseY(target)]

void Xsolve(vector<vector<bool>> &map, const vector<pair<int, int>> water, const vector<pair<int, int>> house);
void Ysolve(vector<vector<bool>> &map, const vector<pair<int, int>> water, const vector<pair<int, int>> house);

// 土地のサイズ
int LandSize;
// 水源の数
int WaterNum;
// 家の数
int HouseNum;
// 消費体力
int Consume;
int finish_house_num = 0;
vector<pair<int, int>> finish_house;
int target = -1;
int x, y;
bool goX = false;
bool goY = false;
int r;
bool skip = false;

void changeTarget(vector<vector<bool>> map, vector<pair<int, int>> water, vector<pair<int, int>> house)
{
    bool w = false;
    target++;
    vector<ll> range(WaterNum + finish_house_num);
    for (int i = 0; i < WaterNum; i++)
    {
        range[i] = sqrt(pow(houseX(target) - water[i].first, 2) + pow(houseY(target) - water[i].second, 2));
    }
    for (int i = 0; i < finish_house_num; i++)
    {
        range[WaterNum + i] = sqrt(pow(houseX(target) - finish_house[i].first, 2) + pow(houseY(target) - finish_house[i].second, 2));
    }
    ll min = INT64_MAX;
    for (int i = 0; i < WaterNum; i++)
    {
        if (range[i] < min)
        {
            min = range[i];
            x = water[i].first;
            y = water[i].second;
            w = true;
        }
    }
    for (int i = 0; i < finish_house_num; i++)
    {
        if (range[WaterNum + i] < min)
        {
            min = range[WaterNum + i];
            x = finish_house[i].first;
            y = finish_house[i].second;
        }
    }
    if (!w)
    {
        if (x != houseX(target))
        {
            if (x < houseX(target))
            {
                x++;
            }
            else
            {
                x--;
            }
            goX = true;
            goY = false;
        }
        else if (y != houseY(target))
        {
            if (y < houseY(target))
            {
                y++;
            }
            else
            {
                y--;
            }
            goY = true;
            goX = false;
        }
    }
}

int getr()
{
    int r;
    cin >> r;
    if (r != 0 && r != 1)
    {
        exit(0);
    }
    return r;
}

void Xsolve(vector<vector<bool>> &map, const vector<pair<int, int>> water, const vector<pair<int, int>> house)
{
    bool difficult = false;
    while (1)
    {
        if (!skip)
            r = getr();
        skip = false;
        if (r == 1)
        {
            difficult = false;
            map[x][y] = true;
            bool change = false;
            if (map[houseX(target)][houseY(target)])
            {
                finish_house.push_back(make_pair(x, y));
                finish_house_num++;
                changeTarget(map,water, house);
                change = true;
            }
            else if (x != houseX(target))
            {
                if (x < houseX(target))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                goX = true;
                goY = false;
            }
            else if (y != houseY(target))
            {
                if (y < houseY(target))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                goY = true;
                goX = false;
            }
            if (map[x][y])
            {
                skip = true;
                continue;
            }
            cout << x << " " << y << " " << BASEPOWER << endl;
        }
        else
        {
            if (difficult && goX)
            {
                while (r == 0)
                {
                    cout << x << " " << y << " " << BIGGERPOWER << endl;
                    r = getr();
                }
                skip = true;
                Ysolve(map, water, house);
            }
            else
            {
                cout << x << " " << y << " " << BIGGERPOWER << endl;
                difficult = true;
            }
        }
    }
}

void Ysolve(vector<vector<bool>> &map, const vector<pair<int, int>> water, const vector<pair<int, int>> house)
{
    bool difficult = false;
    while (1)
    {
        if (!skip)
            r = getr();
        skip = false;
        if (r == 1)
        {
            difficult = false;
            map[x][y] = true;
            bool change = false;
            if (map[houseX(target)][houseY(target)])
            {
                finish_house.push_back(make_pair(x, y));
                finish_house_num++;
                changeTarget(map,water, house);
                change = true;
            }
            else if (y != houseY(target))
            {
                if (y < houseY(target))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                goY = true;
                goX = false;
            }
            else if (x != houseX(target))
            {
                if (x < houseX(target))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                goX = true;
                goY = false;
            }

            if (map[x][y])
            {
                skip = true;
                continue;
            }
            cout << x << " " << y << " " << BASEPOWER << endl;
        }
        else
        {
            if (difficult && goY)
            {
                while (r == 0)
                {
                    cout << x << " " << y << " " << BIGGERPOWER << endl;
                    r = getr();
                }
                skip = true;
                Xsolve(map, water, house);
            }
            else
            {
                cout << x << " " << y << " " << BIGGERPOWER << endl;
                difficult = true;
            }
        }
    }
}

int main()
{
    cin >> LandSize >> WaterNum >> HouseNum >> Consume;
    vector<vector<bool>> map(LandSize, vector<bool>(LandSize, false));
    vector<pair<int, int>> water(WaterNum);
    for (int i = 0; i < WaterNum; i++)
    {
        cin >> water[i].first >> water[i].second;
    }
    sort(water);
    vector<pair<int, int>> house(HouseNum);
    for (int i = 0; i < HouseNum; i++)
    {
        cin >> house[i].first >> house[i].second;
    }
    sort(house);
    changeTarget(map, water, house);
    cout << x << " " << y << " " << BASEPOWER << endl;
    Xsolve(map, water, house);
}