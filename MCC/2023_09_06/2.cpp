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
    string N, K;
    cin >> N >> K;
    if (K[0] == '0' || K[K.size() - 1] == '0')
    {
        cout << 0 << endl;
        return 0;
    }

    ll cnt = 0;
    string r_K = K;
    reverse(r_K);
    if (stoll(r_K) < stoll(K))
    {
        cout << 0 << endl;
        return 0;
    }
    if (K != r_K)
    {
        while (stoll(K) <= stoll(N))
        {
            cnt++;
            K += '0';
        }
    }
    while (stoll(r_K) <= stoll(N))
    {
        cnt++;
        r_K += '0';
    }
    cout << cnt;
}