#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    string s;
    cin >> s;
    int N = s.size();
    int g_cnt = 0;
    int p_cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (s[i] == 'g')
        {
            g_cnt++;
        }
        else
        {
            p_cnt++;
        }
    }
    cout << (g_cnt - p_cnt) / 2;
}