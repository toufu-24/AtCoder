#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int A, B;
    cin >> A >> B;
    if (abs(A - B) == 1 && A % 3 != 0)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}