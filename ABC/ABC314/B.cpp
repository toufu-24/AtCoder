#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<set<int>> A(N);
    for (int i = 0; i < N; i++)
    {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++)
        {
            int tmp;
            cin >> tmp;
            A[i].insert(tmp);
        }
    }
    int X;
    cin >> X;
    vector<int> ans;
    int min_size = 1e9;
    for (int i = 0; i < N; i++)
    {
        if (A[i].count(X))
        {
            if (A[i].size() < min_size)
            {
                min_size = A[i].size();
                ans.clear();
                ans.push_back(i + 1);
            }
            else if (A[i].size() == min_size)
            {
                ans.push_back(i + 1);
            }
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}