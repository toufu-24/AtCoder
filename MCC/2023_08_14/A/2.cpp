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
    int N, X, Y, Z;
    cin >> N >> X >> Y >> Z;
    set<int> pass;
    vector<pair<int, int>> A(N), B(N), sum(N);
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        A[i] = {tmp, -i};
    }
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        B[i] = {tmp, -i};
    }
    for (int i = 0; i < N; i++)
    {
        sum[i] = {A[i].first + B[i].first, -i};
    }
    sort(A);
    reverse(A);
    sort(B);
    reverse(B);
    sort(sum);
    reverse(sum);

    vector<int> ans;
    for (int i = 0; i < X; i++)
    {
        if (pass.count(-A[i].second))
        {
            X++;
            continue;
        }
        ans.push_back(-A[i].second);
        pass.insert(-A[i].second);
    }
    for (int i = 0; i < Y; i++)
    {
        if (pass.count(-B[i].second))
        {
            Y++;
            continue;
        }
        ans.push_back(-B[i].second);
        pass.insert(-B[i].second);
    }
    for (int i = 0; i < Z; i++)
    {
        if (pass.count(-sum[i].second))
        {
            Z++;
            continue;
        }
        ans.push_back(-sum[i].second);
        pass.insert(-sum[i].second);
    }
    sort(ans);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] + 1 << endl;
    }
}