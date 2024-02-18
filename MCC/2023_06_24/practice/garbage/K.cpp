#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m;
    cin >> m;
    for (int q = 0; q < m; q++)
    {
        double n;
        cin >> n;
        double r = sqrt(n / 2);
        printf("%.10lf\n", r);
    }
}