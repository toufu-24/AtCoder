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
    int N;
    cin >> N;
    vector<int> X(5 * N);
    for (int i = 0; i < 5 * N; i++)
    {
        cin >> X[i];
    }
    sort(X);
    double sum = 0;
    for (int i = N; i < 4 * N; i++)
    {
        sum += X[i];
    }
    cout << sum / (3 * N);
}