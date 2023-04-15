#include <bits/stdc++.h>
using namespace std;

int main()
{
    int p;
    cin >> p;
    int price, N;
    // パターン1
    if (p == 1)
    {
        cin >> price >> N;

        cout << price * N << endl;
    }

    // パターン2
    if (p == 2)
    {
        string text;
        cin >> text >> price >> N;

        cout << text << "!" << endl;
        cout << price * N << endl;
    }
}
