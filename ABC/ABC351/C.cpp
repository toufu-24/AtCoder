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

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    deque<int> deq;
    for (int i = 0; i < N; i++)
    {
        deq.push_back(A[i]);
    loop:;
        if (deq.size() < 2)
            continue;
        int a = deq[deq.size() - 1];
        int b = deq[deq.size() - 2];
        if (a == b)
        {
            deq.pop_back();
            deq.pop_back();
            deq.push_back(a + 1);
            goto loop;
        }
    }
    cout << deq.size() << endl;
}
