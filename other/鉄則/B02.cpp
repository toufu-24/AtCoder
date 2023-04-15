#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int A, B;
    cin >> A >> B;
    for (int i = A; i <= B; i++)
    {
        if (100 % i == 0)
        {
            cout << "Yes";
            return 0;
        }
        if (i == 1)
        {
            break;
        }
    }
    cout << "No";
    return 0;
}