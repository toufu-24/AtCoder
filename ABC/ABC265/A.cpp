#include <bits/stdc++.h>
using namespace std;

int main()
{
    int X, Y, N;
    cin >> X >> Y >> N;
    if (X < Y / 3)
    {
        cout << X * N << endl;
    }
    else
    {
        int count = 0;
        while (1)
        {
            N -= 3;
            if (N < 0)
            {
                N += 3;
                break;
            }
            count++;
        }
        cout << Y * count + X * N << endl;
    }
}