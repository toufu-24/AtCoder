#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    sort(a);
    bool flag = false;
    int ans = 0;
    for (int i = 1; i < N; i++)
    {
        while (true)
        {
            if (a[i] == a[0])
            {
                break;
            }
            else if (a[i] < 0)
            {
                flag = true;
                break;
            }
            else if (a[i] % 2 == 0)
            {
                a[i] /= 2;
                ans++;
            }
            else if (a[i] % 3 == 0)
            {
                a[i] /= 3;
                ans++;
            }
            else
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            cout << -1;
            return 0;
        }
    }
    cout << ans;
    return 0;
}