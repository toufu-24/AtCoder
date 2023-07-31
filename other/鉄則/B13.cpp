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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    vector<int> sum(N + 1, 0); // 番兵を置く
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        sum[i + 1] = sum[i] + A[i];
    }

    ll ans = 0;
    int right = 0;
    for (int left = 0; left < N; left++)
    {
        if (right < left)
            right = left; // rightをleftの位置にリセット
        while (right < N && sum[right + 1] - sum[left] <= K)
        {
            right++;
        }
        ans += right - left;
        if (left == right)
            right++; // left == rightの場合、rightをインクリメント
    }
    cout << ans << endl;
}
