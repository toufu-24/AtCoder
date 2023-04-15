#include <bits/stdc++.h>
using namespace std;

int64_t sum(int64_t x)
{
    int64_t num_sum = 0;
    while (x > 0)
    {
        num_sum += x % 10;
        x /= 10;
    }
    return num_sum;
}

int main()
{
    int N;
    cin >> N;
    int64_t M = 0;
    unsigned long long int x = N;
    // TODO 条件変更
    while (x < 10000000000)
    {
        if (sum(x) == N)
        {
            M = max(M, sum(2 * x));
        }
        x++;
    }
    x = N;
    while (true)
    {
        if (sum(x) == N && sum(2 * x) == M)
        {
            break;
        }
        x++;
    }
    cout << M << endl;
    cout << x << endl;
}