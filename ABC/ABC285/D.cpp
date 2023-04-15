#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    double start = clock();
    int N;
    cin >> N;
    vector<string> S(N);
    vector<string> T(N);
    set<pair<string, string>> S_set;
    unordered_set<string> S_only_set;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> T[i];
        S_set.insert(make_pair(S[i], T[i]));
        S_only_set.insert(S[i]);
    }
    bool flag = false;
    while (double(clock() - start) / CLOCKS_PER_SEC < 1.93)
    {
        for (pair<string, string> x : S_set)
        {
            if (S_only_set.count(x.second))
            {
                continue;
            }
            else
            {
                S_set.erase(x);
                S_only_set.erase(x.first);
                S_only_set.insert(x.second);
            }
        }
        if (S_set.empty())
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}