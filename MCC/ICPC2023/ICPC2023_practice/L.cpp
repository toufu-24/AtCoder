#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
    start:
        int n;
        cin >> n;
        if (n == 0)
        {
            return 0;
        }
        vector<int> w(n);
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;
            w[i] = s.size();
        }
        int tank[] = {5, 7, 5, 7, 7};
        for (int i = 0; i < n; ++i)
        {
            int count = 0, sum = 0;
            for (int j = i; j < n; ++j)
            {
                sum += w[j];
                if (sum == tank[count])
                {
                    ++count;
                    sum = 0;
                    if (count == 5)
                    {
                        cout << i + 1 << '\n';
                        goto start;
                    }
                }
            }
        }
    }
}