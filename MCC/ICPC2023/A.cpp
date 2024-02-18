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
        vector<int> a(n);
        int index = 0;
        int min = INT32_MAX;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (abs(a[i] - 2023) < min)
            {
                index = i;
                min = abs(a[i] - 2023);
            }
        }
        cout << index + 1 << "\n";
    }
}