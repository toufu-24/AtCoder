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
    int N;
    cin >> N;
    vector<string> S(N);
    set<string> S_set;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        S_set.insert(S[i]);
    }
    bool ans = true;
    if (S_set.size() != N)
    {
        ans = false;
    }
    for (int q = 0; q < N && ans; q++)
    {
        string s = "HDCS";
        bool flag = false;
        for (int i = 0; i < 4; i++)
        {
            if (s[i] == S[q][0])
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            ans = false;
        }

        string s2 = "A23456789TJQK";
        bool flag2 = false;
        for (int i = 0; i < s2.size(); i++)
        {
            if (s2[i] == S[q][1])
            {
                flag2 = true;
                break;
            }
        }
        if (!flag2)
        {
            ans = false;
        }
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}