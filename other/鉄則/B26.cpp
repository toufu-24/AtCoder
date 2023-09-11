#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define size 1000000 + 1

vector<bool> isPrime(size, true);

int main()
{
    int N;
    cin >> N;
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i < size; i ++)
    {
        if (!isPrime[i])
        {
            continue;
        }
        isPrime[i] = true;
        for (int j = 2; i * j < size; j++)
        {
            isPrime[i * j] = false;
        }
    }
    for (int i = 0; i <= N; i++)
    {
        if (isPrime[i])
        {
            cout << i << endl;
        }
    }
}