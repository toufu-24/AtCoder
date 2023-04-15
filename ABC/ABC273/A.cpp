#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int func(int N)
{
    if (N == 0)
    {
        return 1;
    }
    return N * func(N - 1);
}

int main()
{
    int N;
    cin >> N;
    cout << func(N);
}