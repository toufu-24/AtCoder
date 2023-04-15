#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int A, B;
    cin >> A >> B;
    if (A == B * 2 && A == B * 2 + 1 && B == A * 2 && B == A * 2 + 1)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}