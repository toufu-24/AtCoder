#include <bits/stdc++.h>
#define rep(i, s, n) for (int i = (s); i < (int)n; i++)
#define sort(vec) sort(vec.begin(), vec.end());
#define reverse(vec) reverse(vec.begin(), vec.end());
#define test_print(vec, n)              \
    rep(i, 0, n) cout << vec[i] << " "; \
    cout << endl;
using namespace std;

bool ver(vector<int> check_num)
{
    int count;
    rep(i, 1, 101)
    {
        count = 0;
        rep(j, 0, 26) if (check_num[j] == i)
            count++;
        if (count != 0 and count != 2)
            return false;
    }
    return true;
}

int main()
{
    int count;
    string S;
    cin >> S;
    string check = "abcdefghijklmnopqrstuvwxyz";
    vector<int> check_num(26);
    // i回の確認
    rep(i, 0, 26)
    {
        char ch = check[i];
        count = 0;
        rep(j, 0, S.size())
        {
            if (S[j] == ch)
                count++;
        }
        check_num[i] = count;
    }
    if (ver(check_num))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}