#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 < 3 && i % 10 >= 0)
        {
            cout << '1';
        }
        else if (i % 10 >= 3 && i % 10 < 6)
        {
            cout << '2';
        }
        else
        {
            cout << '3';
        }
        cout << ' ';
    }
}