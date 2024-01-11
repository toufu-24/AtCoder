#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, W;
    cin >> N >> W;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    set<int> ans;
    for (int i = 0; i < N; i++)
    {
        int sum1 = A[i];
        if (sum1 <= W)
        {
            ans.insert(sum1);
        }
        for (int j = i + 1; j < N; j++)
        {
            int sum2 = A[i] + A[j];
            if (sum2 <= W)
            {
                ans.insert(sum2);
            }
            for (int k = j + 1; k < N; k++)
            {
                int sum3 = A[i] + A[j] + A[k];
                if (sum3 <= W)
                {
                    ans.insert(sum3);
                }
            }
        }
    }
    cout << ans.size() << endl;
}