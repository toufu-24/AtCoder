#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        ll N;
        cin >> N;
        ll sq = sqrt(N);
        ll j;
        for (j = 2; j <= sq; j += 2)
        {
            if (N % j == 0)
            {
                break;
            }
            if (j == 2)
            {
                j--;
            }
        }
        if (N % (j * j) == 0)
        {
            cout << j << " " << N / (j * j) << endl;
        }
        else
        {
            ll tmp = sqrt(N / j);
            cout << tmp << " " << j << endl;
        }
    }
}