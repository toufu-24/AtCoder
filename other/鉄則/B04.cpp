#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    string N;
    cin >> N;
    int ans = 0;
    for (int i = 0; i < N.size(); i++)
    {
        if (N[i] == '1')
        {
            ans += pow(2, N.size() - i - 1);
        }
    }
    cout << ans;
}