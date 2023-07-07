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
    ll K;
    cin >> K;
    ll K_base = K;
    // 素因数分解
    vector<ll> prime;
    while (1)
    {
        bool flag = false;
        for (int i = 2; i < sqrt(K); i++)
        {
            if (K % i == 0)
            {
                prime.push_back(i);
                K /= i;
                flag = true;
                break;
            }
        }
        if (!flag)
            break;
    }
    if (K != 1)
        prime.push_back(K);
    sort(prime);
    ll a = 0;
    for (int i = 0; i < prime.size(); i++)
    {
        a += prime[i];
    }
    
    cout << prime[prime.size() - 1] + a << endl;
}