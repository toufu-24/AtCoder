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
    int N, M;
    cin >> N >> M;
    vector<int> L(M);
    vector<int> R(M);
    for (int i = 0; i < M; i++)
    {
        cin >> L[i] >> R[i];
    }
    int L_max = *max_element(all(L));
    int R_min = *min_element(all(R));
    if (R_min < L_max)
        cout << 0;
    else
        cout << R_min - L_max + 1;
}
