#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int main()
{

    double X, K;
    cin >> X >> K;
    for (int i = 0; i < K; i++)
    {
        X /= pow(10, i + 1);
        X = round(X);
        X *= pow(10, i + 1);
    }
    printf("%.0lf", X);
}