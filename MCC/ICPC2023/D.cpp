#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }
        string S;
        cin >> S;

        vector<int> need_point;
        for (int i = 1; i < S.size(); i++)
        {
            if (S[i] == 'o')
            {
                need_point.push_back(i);
            }
        }
        if (need_point.size() == 0)
        {
            cout << 1 << "\n";
        }

        set<int> able_make;
        int cnt = 0;
        for (int i = 0; i < need_point.size(); i++)
        {
            if (able_make.count(need_point[i]))
            {
                continue;
            }
            for (auto x : able_make)
            {
                able_make.insert(abs(need_point[i] - x));
            }
            able_make.insert(need_point[i]);
            cnt++;
        }

        cout << cnt << "\n";
    }
}