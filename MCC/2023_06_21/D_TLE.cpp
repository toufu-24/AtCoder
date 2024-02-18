#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int n = 9;
    vector<int> tmp = {1, 3, 3, 3, 3, 3, 3, 4, 4};
    vector<int> b(n);

    while (1)
    {
        for (int i = 0; i < n; i++)
        {
            b[i] = tmp[i];
        }

        ll ans = 0;
        while (1)
        {
            bool three_get = false;
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (b[i] != 0)
                {
                    b[i]--;
                    cnt++;
                }
                if (cnt == 3)
                {
                    three_get = true;
                    ans++;
                    break;
                }
            }
            if (!three_get)
            {
                break;
            }
        }
        if (ans == 9)
        {
            for (int i = 0; i < n; i++)
            {
                cout << tmp[i] << " ";
            }
            cout << endl;
        }
        next_permutation(all(tmp));
    }
}