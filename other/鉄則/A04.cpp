#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    string bina(10, '0');
    for (int i = 0; true; i++)
    {
        if (N == 0)
        {
            break;
        }
        bina[i] = char(N % 2 + '0');
        N /= 2;
    }
    reverse(all(bina));
    cout << bina;
}