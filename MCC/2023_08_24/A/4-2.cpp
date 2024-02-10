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
    int N;
    cin >> N;
    string S;
    cin >> S;
    list<int> A;
    auto itr = A.begin();
    A.insert(itr, 0);
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'L')
        {
            itr--;
        }
        A.insert(itr, i + 1);
    }

    for_each(all(A), [](int x)
             { cout << x << " "; });
}