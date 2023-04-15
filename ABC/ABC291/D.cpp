#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

using mint = modint998244353;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
    }
    // あっても4N
    ll cnt = 0;
    ll three = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int tmp = 0;
        bool a = false, b = false;
        if (A[i] == A[i + 1])
        {
            tmp++;
            a = true;
        }
        if (A[i] == B[i + 1])
        {
            tmp++;
            a = true;
        }
        if (B[i] == A[i + 1])
        {
            tmp++;
            b = true;
        }
        if (B[i] == B[i + 1])
        {
            tmp++;
            b = true;
        }
        if (tmp == 1)
        {
            cnt++;
        }
        else if (tmp == 2)
        {
            cnt += 2;
        }
        else if (tmp == 3)
        {
            cnt += 2;
        }
        else if (tmp == 4)
        {
            cout << 0;
            return 0;
        }
        if (a)
        {
            if (i != 0 && (A[i] == A[i - 1]))
            {
                three++;
            }
            if (i != 0 && (A[i] == B[i - 1]))
            {
                three++;
            }
        }
        if (b)
        {
            if (i != 0 && (B[i] == A[i - 1]))
            {
                three++;
            }
            if (i != 0 && (B[i] == B[i - 1]))
            {
                three++;
            }
        }
    }
    mint sum = 0;
    for (int i = 1; i <= cnt; i++)
    {
        mint po = 2;
        sum += po.pow(N - 2);
    }
    for (int i = 0; i < three; i++)
    {
        mint p = 2;
        sum -= p.pow(N - 4);
    }
    mint all = 2;
    all = all.pow(N);
    mint ans = all - sum;
    cout << ans.val();
}