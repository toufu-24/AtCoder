#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int N, X;
    cin >> N >> X;
    bool ans = false;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp == X)
        {
            ans = true;
        }
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}