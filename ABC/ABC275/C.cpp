#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int ans = 0;

void judge(int i, int j, vector<string> S)
{
    for (int k = j + 1; k < S[i].size(); k++)
    {
        if (S[i][k] == '#')
        {
            for (int l = i + 1; l < S.size(); l++)
            {
                if (S[l][j] == '#' && S[l][k] == '#')
                {
                    ans++;
                }
            }
        }
    }
}

int main()
{
    vector<string> S(9);
    for (int i = 0; i < 9; i++)
    {
        cin >> S[i];
    }
    for (int big = 0; big < 9; big++)
    {
        vector<string> arr;
        for (int i = 0; i < 9; i++)
        {
            arr.push_back(S[i]);
        }
        for (int i = 0; i < S.size(); i++)
        {
            for (int j = 0; j < S[i].size(); j++)
            {
                if (big == 0 && S[i][j] == '#')
                {
                    judge(i, j, S);
                }
                else if (S[i][j] == '#')
                {
                    judge(i, j, arr);
                }
            }
        }
    }
}