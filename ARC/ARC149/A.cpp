#include <bits/stdc++.h>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main()
{
    int N, M;
    cin >> N >> M;
    bool ans_flag = false;
    int digit = log10(M) + 1;
    string ans;
    mp::cpp_int num;
    for (int i = N; i >= digit; i--)
    {
        for (int j = 9; j >= 1; j--)
        {
            vector<char> tmp(i, j + '0');
            string all(tmp.begin(), tmp.end());
            num.assign(all);
            if (num % M == 0)
            {
                ans_flag = true;
                ans = num.str();
                break;
            }
        }
        if (ans_flag)
        {
            break;
        }
        /*if ((double)(double(clock()) / double(CLOCKS_PER_SEC)) > 1.0)
        {
            break;
        }*/
    }
    /*if (!ans_flag)
    {
        for (int i = digit; i <= N; i++)
        {
            for (int j = 9; j >= 1; j--)
            {
                vector<char> tmp(i, j + '0');
                string all(tmp.begin(), tmp.end());
                num.assign(all);
                if (num % M == 0)
                {
                    ans = num.str();
                }
            }
            if ((double)(double(clock()) / double(CLOCKS_PER_SEC)) > 1.9)
            {
                break;
            }
        }
    }*/
    if (ans_flag)
    {
        cout << ans << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}