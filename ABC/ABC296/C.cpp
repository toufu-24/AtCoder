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
    int N, X;
    cin >> N >> X;
    vector<int> A(N);
    set<int> num;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        num.insert(A[i]);
    }
    bool flag = false;
    for (int i = 0; i < N; i++)
    {
        if (num.count(A[i] - X))
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}