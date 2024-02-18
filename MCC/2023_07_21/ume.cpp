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
    cout << 0;
    for (int i = 1; i < 1000; i++)
    {
        if (i % 8 == 0)
            printf(", \"%03d\"", i);
    }
}