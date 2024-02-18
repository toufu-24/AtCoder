#include <bits/stdc++.h>
using namespace std;
#define ll int64_t

int main()
{
    while (true)
    {
        ll s;
        cin >> s;
        while (s == 0)
        {
            break;
        }
        // 素因数分解
        vector<int> prime;
        while (s != 1)
        {
            bool flag = false;
            double sq = sqrt(s);
            for (int i = 2; i <= sq; i++)
            {
                if (s % i == 0)
                {
                    prime.push_back(i);
                    s /= i;
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                prime.push_back(s);
                break;
            }
        }
        for (int i = 0; i < prime.size(); i++)
        {
            cerr << prime[i] << " ";
        }
        cerr << "\n";
    }
}