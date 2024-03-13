#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int A, B;
    cin >> A >> B;
    for (int i = 0; i < 10; i++)
    {
        if (i != A + B)
        {
            cout << i << endl;
            return 0;
        }
    }
}