#include <bits/stdc++.h>
using namespace std;
const int64_t rule_num = 998244353;

int main()
{
    int64_t N;
    cin >> N;
    int64_t x;
    x = abs(N) % rule_num;
    if (N < 0)
    {
        x = rule_num - x;
    }
    if (x >= rule_num)
    {
        x -= rule_num;
    }
    if ((N - x) % rule_num == 0)
        cout << x << endl;
}