#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int A, B;
    cin >> A >> B;
    int64_t ans = 1;
    for (int i = 0; i < B; i++)
    {
        ans *= A;
    }
    cout << ans;
}