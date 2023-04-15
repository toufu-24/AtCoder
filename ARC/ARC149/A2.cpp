#include <bits/stdc++.h>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main()
{
    int N, M;
    cin >> N >> M;
    bool ans_flag = false;
    string ans_tmp, ans;
    mp::cpp_int num;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            vector<char> tmp(i, j + '0');
            string all(tmp.begin(), tmp.end());
            num.assign(all);
            if (num % M == 0)
            {
                ans_flag = true;
                ans_tmp = num.str();
            }
        }
        if (ans_flag)
        {
            while (ans.length() <= N)
            {
                ans += ans_tmp;
            }
            break;
        }
    }
    if (ans_flag)
    {
        for (int i = 0; i < ans.size() - ans_tmp.size(); i++)
        {
            cout << ans[i];
        }
    }
    else
    {
        cout << -1 << endl;
    }
}