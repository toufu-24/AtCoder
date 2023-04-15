#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M, X, T, D;
    cin >> N >> M >> X >> T >> D;
    if (M < X)
    {
        int distance = X - M;
        for (int i = 0; i < distance; i++)
        {
            T -= D;
        }
    }

    cout << T;
}