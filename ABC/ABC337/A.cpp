#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<int> X(N);
    vector<int> Y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i] >> Y[i];
    }
    int x_sum = reduce(all(X));
    int y_sum = reduce(all(Y));
    if (x_sum > y_sum)
        cout << "Takahashi" << endl;
    else if (x_sum == y_sum)
    {
        cout << "Draw" << endl;
    }
    else
        cout << "Aoki" << endl;
}