#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        if(rand() % 2)
            cout << "Set A\n";
        else
            cout << "Set B\n";
    }
}