#include <bits/stdc++.h>
using namespace std;

int main()
{
    int K;
    cin >> K;
    int H = 21;
    int M = 0;
    while (1)
    {
        if (K >= 60)
        {
            H++;
            if (H == 24)
            {
                H = 0;
            }
            K -= 60;
        }
        else
        {
            M += K;
            break;
        }
    }
    printf("%02d:%02d", H, M);
}