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
    vector numple(9, vector(9, 0));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> numple[i][j];
        }
    }

    // 行
    for (int i = 0; i < 9; i++)
    {
        set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; j++)
        {
            s.erase(numple[i][j]);
        }
        if (!s.empty())
        {
            cout << "No" << endl;
            return 0;
        }
    }

    // 列
    for (int i = 0; i < 9; i++)
    {
        set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; j++)
        {
            s.erase(numple[j][i]);
        }
        if (!s.empty())
        {
            cout << "No" << endl;
            return 0;
        }
    }

    // 3*3
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            set<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (int k = i; k < i + 3; k++)
            {
                for (int l = j; l < j + 3; l++)
                {
                    s.erase(numple[k][l]);
                }
            }
            if (!s.empty())
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
}