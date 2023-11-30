#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    unordered_multiset<int> s;
    for (int i = 0; i < N; i++)
    {
        s.insert(A[i]);
    }
    vector<int> sorted = A;
    SORT(sorted);
    int mex = 1;
    for (int i = 0; i < N; i++)
    {
        if (sorted[i] == mex)
        {
            mex++;
        }
    }
    cerr << mex << endl;
    for (int q = 0; q < Q; q++)
    {
        int i, x;
        cin >> i >> x;
        i--;
        int ori_A_i = A[i];
        s.erase(s.find(A[i]));
        if (x < mex)
        {
            if (s.find(x) == s.end())
            {
                mex = x;
            }
        }
        if (x == mex)
        {
            mex++;
            while (s.find(mex) != s.end())
            {
                mex++;
            }
        }
        if (ori_A_i < mex)
        {
            if (s.find(ori_A_i) == s.end())
            {
                mex = ori_A_i;
            }
        }

        A[i] = x;
        s.insert(A[i]);
        cout << mex << '\n';
    }
}
