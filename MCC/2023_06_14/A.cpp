#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    while (1)
    {
        int D, E;
        cin >> D >> E;
        if (D == 0 && E == 0)
        {
            break;
        }
        double min = 1000000;
        for (int i = 0; i <= D; i++)
        {
            int j = D - i;
            double zure = abs(sqrt(i * i + j * j) - E);
            if (zure < min)
            {
                min = zure;
            }
        }
        cout << min << endl;
    }
}