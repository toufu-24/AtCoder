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
        vector<char> d(n);
        for (int i = 0; i < n; i++)
        {
            cin >> d[i];
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (d[i] == '2')
            {
                string judge;
                for (int j = 0; j < 4; j++)
                {
                    if (i + j >= n)
                    {
                        break;
                    }
                    judge += d[i + j];
                }
                if (judge == "2020")
                {
                    cnt++;
                }
            }
        }
        cout << cnt << "\n";
    }
}
