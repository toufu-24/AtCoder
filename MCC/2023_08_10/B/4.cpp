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
    modint::set_mod(1000000007);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    ll now;
    if (N % 2 == 0)
    {
        now = 1;
    }
    else
    {
        now = 0;
    }
    for (int i = 0; i < A.size(); i++, now += 2)
    {
        if (A[i] == 0)
        {
            if (i + 1 < N && A[i + 1] == 0)
            {
                cout << 0;
                return 0;
            }
        }
        else if (A[i] == A[i + 1])
        {
            if ((i + 2 < N && A[i + 1] == A[i + 2]) || now != A[i])
            {
                cout << 0;
                return 0;
            }
            i++;
        }
        else
        {
            cout << 0;
            return 0;
        }
    }

    A.erase(unique(all(A)), A.end());
    modint ans = 0;
    int size = A.size();
    if (N % 2 == 1)
    {
        size--;
    }
    modint kisuu = 2;
    ans = kisuu.pow(size);
    cout << ans.val() << endl;
}