#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int sum = 0;
        for (int j = 0; j < 7; j++)
        {
            int a;
            cin >> a;
            sum += a;
        }
        cout << sum << " ";
    }
}