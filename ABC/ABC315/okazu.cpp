#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> fs(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        fs[i] = make_pair(a, b);
    }
    sort(fs.begin(), fs.end(),
         [](pair<int, int> a, pair<int, int> b)
         { return a.second > b.second; });
    long long max = 0;
    for (int i = 1; i < n; i++)
    {
        if (fs[i].first != fs[0].first)
        {
            max = fs[i].second + fs[0].second > max ? fs[i].second + fs[0].second : max;
            break;
        }
        else if (fs[i].first == fs[i - 1].first)
        {
            max = fs[i - 1].second + fs[i].second / 2 > max ? fs[i - 1].second + fs[i].second / 2 : max;
        }
    }
    cout << max << endl;
    return 0;
}
