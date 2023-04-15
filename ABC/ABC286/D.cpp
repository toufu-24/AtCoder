#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int N, X;
vector<int> A, B;

bool money(int cnt, int remain)
{
    for (int i = 0; i <= B[cnt]; i++)
    {
        if (cnt != N - 1)
            if (money(cnt + 1, remain))
            {
                return true;
            }
        remain -= A[cnt];
        if (remain == 0)
        {
            return true;
        }
        else if (remain < 0)
        {
            return false;
        }
    }
    return false;
}

int main()
{
    cin >> N >> X;
    vector<int> Atmp(N);
    vector<int> Btmp(N);
    for (int i = 0; i < N; i++)
    {
        cin >> Atmp[i] >> Btmp[i];
    }
    A = Atmp;
    B = Btmp;
    int remain = X;
    if (money(0, remain))
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}