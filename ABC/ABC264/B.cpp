#include <bits/stdc++.h>
using namespace std;

const int length = 15;

bool judge(int i, int j)
{
    for (int k = 1; k < 8; k++)
    {
        if (k % 2 == 1)
        {
            if (i == k || i == length - k + 1 || j == k || j == length - k + 1)
                return true;
        }
        else if (i == k || i == length - k + 1 || j == k || j == length - k + 1)
            return false;
    }
}

int main()
{
    int R, C;
    cin >> R >> C;
    if (judge(R, C))
        cout << "black";
    else
        cout << "white";
}