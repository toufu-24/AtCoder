#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    while (1)
    {
        int a[4];
        bool br = true;
        for (int i = 0; i < 4; i++)
        {
            cin >> a[i];
            if (a[i] != 0)
            {
                br = false;
            }
        }
        if (br)
        {
            break;
        }

        while (1)
        {
            int zero = 0;
            int minimum = INT32_MAX;
            int min_index = -1;
            for (int i = 0; i < 4; i++)
            {
                if (a[i] != 0 && minimum > a[i])
                {
                    minimum = a[i];
                    min_index = i;
                }
                if (a[i] == 0)
                {
                    zero++;
                }
            }
            if (zero == 3)
            {
                break;
            }
            for (int i = 0; i < 4; i++)
            {
                if (i == min_index)
                {
                    continue;
                }
                a[i] -= minimum;
                if (a[i] < 0)
                {
                    a[i] = 0;
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if (a[i] != 0)
            {
                cout << a[i] << "\n";
                break;
            }
        }
    }
}