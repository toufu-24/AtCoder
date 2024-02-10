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
    char b;
    cin >> b;
    switch (b)
    {
    case 'A':
        cout << 'T';
        break;
    case 'T':
        cout << 'A';
        break;
    case 'G':
        cout << 'C';
        break;
    case 'C':
        cout << 'G';
        break;
    }
}