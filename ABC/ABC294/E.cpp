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
    ll L, N1, N2;
    cin >> L >> N1 >> N2;
    vector<int> v1(N1);
    vector<int> l1(N1);
    for (int i = 0; i < N1; i++)
    {
        cin >> v1[i] >> l1[i];
    }

    vector<int> v2(N2);
    vector<int> l2(N2);
    for (int i = 0; i < N2; i++)
    {
        cin >> v2[i] >> l2[i];
    }

    // 何個目の分割か
    ll one = 0, two = 0;
    ll one_left = 0, two_left = 0;
    ll ans = 0;
    for (ll i = 0; i < L;)
    {
        ll min;
        if (l1[one] - (i - one_left) < l2[two] - (i - two_left))
        {
            min = abs(l1[one] - (i - one_left));
            one_left += l1[one];
            one++;
            if (v1[one - 1] == v2[two])
            {
                ans += min;
            }
        }
        else if (l1[one] - (i - one_left) > l2[two] - (i - two_left))
        {
            min = abs(l2[two] - (i - two_left));
            two_left += l2[two];
            two++;
            if (v1[one] == v2[two - 1])
            {
                ans += min;
            }
        }
        else
        {
            min = abs(l2[two] - (i - two_left));
            one_left += l1[one];
            two_left += l2[two];
            one++;
            two++;
            if (v1[one - 1] == v2[two - 1])
            {
                ans += min;
            }
        }
        i += min;
    }
    cout << ans;
}