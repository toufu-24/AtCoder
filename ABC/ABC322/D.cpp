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

int main()
{
    int cnt = 0;
    vector P1(4, vector<char>(4));
    vector P2(4, vector<char>(4));
    vector P3(4, vector<char>(4));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> P1[i][j];
            if (P1[i][j] == '#')
            {
                cnt++;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> P2[i][j];
            if (P2[i][j] == '#')
            {
                cnt++;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> P3[i][j];
            if (P3[i][j] == '#')
            {
                cnt++;
            }
        }
    }
    if (cnt == 16)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}