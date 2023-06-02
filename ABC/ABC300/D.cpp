#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    ll N;
    cin >> N;
    ll up_a = pow(N, 1 / double(5));
    vector<ll> a_prime;
    for (int i = 2; i <= up_a; i++)
    {
        // i が素数かどうか
        bool is_prime = true;
        double sq = sqrt(i);
        for (int j = 2; j <= sq; j++)
        {
            if (i % j == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
        {
            a_prime.push_back(i);
        }
    }

    ll size = a_prime.size();
    vector<ll> a_eliminated;
    for (int i = 0; i < size; i++)
    {
        a_eliminated.push_back(N / pow(a_prime[i], 2));
    }

    ll ans = 0;
    for (int i = 0; i < size; i++)
    {
        double eli = pow(a_eliminated[i], 1 / double(3));
        for (int j = a_prime[i] + 1; j <= eli; j++)
        {
            bool is_prime = true;
            double sq = sqrt(j);
            for (int k = 2; k <= sq; k++)
            {
                if (j % k == 0)
                {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime)
            {
                ll c_up = sqrt(a_eliminated[i] / j);
                for (int k = j + 1; k <= c_up; k++)
                {
                    bool is_prime2 = true;
                    double sq = sqrt(k);
                    for (int l = 2; l <= sq; l++)
                    {
                        if (k % l == 0)
                        {
                            is_prime2 = false;
                            break;
                        }
                    }
                    if (is_prime2)
                    {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans;
}