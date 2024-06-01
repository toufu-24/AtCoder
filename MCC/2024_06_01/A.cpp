#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }
        vector<int> d(n);
        for (int i = 0; i < n; i++)
        {
            cin >> d[i];
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (d[i] != 2)
            {
                continue;
            }
            string tmp;
            for (int j = 0; j < 4; j++)
            {
                if (i + j >= n)
                {
                    break;
                }
                tmp += to_string(d[i + j]);
            }
            if (tmp == "2020")
            {
                ans++;
            }
        }
        cout << ans << endl;
    }
}
