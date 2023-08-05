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
    int N;
    cin >> N;
    vector<int> P(N);
    vector<int> sorted_P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    int need = 0;
    for (int i = 1; i < N; i++)
    {
        if (P[0] < P[i])
            need = max(need, P[i] - P[0] + 1);
        else if (P[0] == P[i])
            need = max(need, 1);
    }
    cout << need << endl;
}