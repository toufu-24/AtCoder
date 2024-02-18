#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            break;
        }
        vector<int> a(n);
        vector<int> b(m);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }
        map<char, int> cnt;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int tmp = a[i] * b[j];
                string S = to_string(tmp);
                for (int k = 0; k < S.size(); k++)
                {
                    cnt[S[k]]++;
                }
            }
        }

        for (int i = 0; i < 9; i++)
        {
            char num = i + '0';
            cout << cnt[num] << " ";
        }
        cout << cnt['9'];
        cout << "\n";
    }
}