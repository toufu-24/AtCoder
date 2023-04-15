#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int N_tmp = N;
    string ans = "00";
    int tmp = N % 16;
    if (tmp < 10)
    {
        ans[1] = tmp + '0';
    }
    else
    {
        if (tmp == 10)
        {
            ans[1] = 'A';
        }
        else if (tmp == 11)
        {
            ans[1] = 'B';
        }
        else if (tmp == 12)
        {
            ans[1] = 'C';
        }
        else if (tmp == 13)
        {
            ans[1] = 'D';
        }
        else if (tmp == 14)
        {
            ans[1] = 'E';
        }
        else if (tmp == 15)
        {
            ans[1] = 'F';
        }
    }
    N /= 16;
    tmp = N % 16;
    if (N_tmp >= 16)
        if (tmp < 10 && tmp != 0)
        {
            ans[0] = tmp + '0';
        }
        else
        {
            if (tmp == 10)
            {
                ans[0] = 'A';
            }
            else if (tmp == 11)
            {
                ans[0] = 'B';
            }
            else if (tmp == 12)
            {
                ans[0] = 'C';
            }
            else if (tmp == 13)
            {
                ans[0] = 'D';
            }
            else if (tmp == 14)
            {
                ans[0] = 'E';
            }
            else if (tmp == 15)
            {
                ans[0] = 'F';
            }
        }
    cout << ans;
}