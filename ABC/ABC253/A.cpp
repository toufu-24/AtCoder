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
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    int b = a[1];
    sort(a, a + 3);
    if (b == a[1])
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}