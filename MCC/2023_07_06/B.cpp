#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int m, n, p;
        cin >> m >> n >> p;
        if (m == 0 && n == 0 && p == 0)
        {
            break;
        }
        set<int> infecter;
        infecter.insert(p);
        vector<pair<int, int>> people(n);
        for (int i = 0; i < n; i++)
        {
            cin >> people[i].first >> people[i].second;
            if (infecter.count(people[i].first))
            {
                infecter.insert(people[i].second);
            }
            if (infecter.count(people[i].second))
            {
                infecter.insert(people[i].first);
            }
        }
        cout << infecter.size() << "\n";
    }
}