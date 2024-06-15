#include <bits/stdc++.h>
using namespace std;

int solve(int, int);

int main(void)
{
    while (1)
    {
        int h, w;
        cin >> h >> w;
        if (h == 0)
            return 0;
        else
            solve(h, w);
    }
}

int solve(int h, int w)
{
    map<char, pair<int, int>> mp;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char tmp;
            cin >> tmp;
            mp[tmp] = make_pair(i, j);
        }
    }
    string s;
    cin >> s;
    int ans = 0;
    ans += mp[s[0]].first + mp[s[0]].second;
    for (int i = 1; i < s.length(); i++)
    {
        ans += abs(mp[s[i]].first - mp[s[i - 1]].first) + abs(mp[s[i]].second - mp[s[i - 1]].second);
    }
    ans += s.length();
    cout << ans << endl;
    return 0;
}