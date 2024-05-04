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
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    vector<pair<int, int>> big(N);
    vector<int> head(N);
    int kata_sum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
        big[i] = {A[i], B[i]};
        kata_sum += A[i];
        head[i] = B[i] - A[i];
    }
    kata_sum += *max_element(all(head));
    cout << kata_sum << endl;
}
