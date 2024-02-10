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
    vector<int> perm_P(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        perm_P[i] = P[i];
    }
    int p_num = 1;
    sort(perm_P);
    do
    {
        if (perm_P == P)
            break;
        p_num++;
    } while (next_permutation(all(perm_P)));

    vector<int> Q(N);
    vector<int> perm_Q(N);
    for (int i = 0; i < N; i++)
    {
        cin >> Q[i];
        perm_Q[i] = Q[i];
    }
    sort(perm_Q);
    int q_num = 1;
    do
    {
        if (perm_Q == Q)
            break;
        q_num++;
    } while (next_permutation(all(perm_Q)));

    cout << abs(p_num - q_num);
}