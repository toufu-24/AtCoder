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
    int N, T;
    cin >> N >> T;
    bool T_flag = false;
    vector<pair<int, int>> T_C;
    vector<pair<int, int>> first_C;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }
    vector<int> R(N);
    for (int i = 0; i < N; i++)
    {
        cin >> R[i];
        
        if (C[i] == T)
        {
            T_flag = true;
            T_C.push_back(make_pair(R[i], i));
        }
        if (C[i] == C[0])
        {
            first_C.push_back(make_pair(R[i], i));
        }
    }

    if (T_flag)
    {
        sort(T_C);
        int max_index = T_C[T_C.size() - 1].second;
        cout << max_index +1 << endl;
    }
    else
    {
        sort(first_C);
        int max_index = first_C[first_C.size() - 1].second;
        cout << max_index +1 << endl;
    }
}