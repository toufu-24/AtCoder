#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    string S;
    cin >> N >> S;
    bool flag1 = false;
    bool flag2 = true;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'o')
        {
            flag1 = true;
        }
        else if (S[i] == 'x')
        {
            flag2 = false;
            break;
        }
    }
    if (flag1 && flag2)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}