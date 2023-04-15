#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

char table[4] = {'F', 'B', 'L', 'R'};

int main()
{
    int kind[100];
    int p;
    for (int i = 0; i < 100; i++)
    {
        cin >> kind[i];
    }
    for (int i = 0; i < 100; i++)
    {
        cin >> p;
        if (kind[i] == 3)
        {
            cout << 'F';
        }
        else
        {
            cout << 'L';
        }

        cout << endl;
        cout << flush;
    }
}