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
        int maximum = -1;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            maximum = max(maximum, tmp);
        }
        cout << maximum << "\n";
    }
}