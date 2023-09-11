#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

bool isPrime(int X)
{
    if (X == 1)
    {
        return false;
    }
    for (int i = 2; i * i <= X; i++)
    {
        if (X % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int Q;
    cin >> Q;
    vector<int> X(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> X[i];
        if (isPrime(X[i]))
        {
            cout << "Yes";
        }
        else
        {
            cout << "No";
        }
        cout << endl;
    }
}