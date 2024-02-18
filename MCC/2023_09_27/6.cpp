#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int a, b;
    char c;
    cin >> a >> c >> b;
    switch (c)
    {
    case '+':
        cout << a + b << endl;
        break;
    case '-':
        cout << a - b;
    case 'x':
        cout << a * b;
    case '/':
        cout << a / b;
    default:
        break;
    }
}