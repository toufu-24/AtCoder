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
    int N;
    cin >> N;
    bitset<32> b(N);
    string s = b.to_string();
    int one = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '1')
        {
            one = i;
            break;
        }
    }
    if (b.count() == 1)
    {
        one++;
    }
    one = s.size() - one;
    cout << one << endl;
    vector<vector<int>> out(one);
    for (int bits = 0; bits <= N; bits++)
    {
        bitset<32> tmp(bits);
        string t = tmp.to_string();
        REVERSE(t);
        for (int i = 0; i < one; i++)
        {
            if (t[i] == '1')
            {
                out[i].push_back(bits);
            }
        }
    }

    for (int i = 0; i < one; i++)
    {
        cout << out[i].size() << " ";
        for (int j = 0; j < out[i].size(); j++)
        {
            cout << out[i][j] << " ";
        }
        cout << endl;
    }

    string S;
    cin >> S;
    int num = 0;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '1')
        {
            num += (1 << i);
        }
    }
    if (num == 0)
    {
        cout << N << endl;
        return 0;
    }
    cout << num << endl;
}