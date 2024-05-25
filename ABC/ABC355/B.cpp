#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<int> C;
    vector<int> A(N), B(M);
    set<int> A_st;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A_st.insert(A[i]);
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    C.insert(C.end(), all(A));
    C.insert(C.end(), all(B));
    SORT(C);
    bool prev = false;
    bool ans = false;
    for (int i = 0; i < N + M; i++)
    {
        if (A_st.contains(C[i]))
        {
            if (prev)
            {
                ans = true;
            }
            prev = true;
        }
        else
        {
            prev = false;
        }
    }
    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
