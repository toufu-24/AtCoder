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
    vector<int> A(N);
    set<int> yet;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        yet.insert(i + 1);
    }
    for (int i = 1; i <= N; i++)
    {
        if (yet.count(i))
        {
            yet.erase(A[i-1]);
        }
    }
    cout << yet.size() << endl;
    for (auto x : yet)
    {
        cout << x << " ";
    }
}