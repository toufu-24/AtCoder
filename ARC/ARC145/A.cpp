#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;

    bool flag = true;

    if ((S.at(0) == 'A' && S.at(N - 1) != 'A') || (S.at(N - 1) == 'B' && S.at(0) != 'B'))
        flag = false;
    if (S.size() == 2 && S.at(0) == 'B' && S.at(N - 1) == 'A')
        flag = false;

    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}