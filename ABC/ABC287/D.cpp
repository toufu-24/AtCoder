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
    string tmp, T;
    cin >> tmp >> T;
    for (int i = 0; i < T.size() + 1; i++)
    {
        string S = tmp.substr(0, i) + tmp.substr(tmp.length() - T.length() + i);
        bool flag = true;
        for (int j = 0; j < T.size(); j++)
        {
            if (!(S[j] == '?' || T[j] == '?' || S[j] == T[j]))
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}