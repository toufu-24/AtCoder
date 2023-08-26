#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

string shift(string S, vector<int> indexes)
{
    string res = S;
    for (int i = 0; i < indexes.size() - 1; i++)
    {
        res[indexes[i + 1]] = S[indexes[i]];
    }
    res[indexes[0]] = S[indexes[indexes.size() - 1]];
    return res;
}

int main()
{
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    vector<vector<int>> color_indexes(M);
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        C[i]--;
        color_indexes[C[i]].push_back(i);
    }

    for (int i = 0; i < M; i++)
    {
        S = shift(S, color_indexes[i]);
    }
    cout << S;
}