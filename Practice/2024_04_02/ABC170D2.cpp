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
    vector<int> A(N), cnt(1e6 + 99, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        cnt[A[i]]++;
    }
    int max_a = *max_element(all(A));
    for (int i = 1; i <= max_a; i++)
    {
        // iがないときはスキップ
        if (cnt[i] == 0)
            continue;
        // iが複数あるときは互いに割れるので、ダメ
        if (cnt[i] > 1)
            cnt[i] = 0;
        // iの倍数を排除
        for (int j = i * 2; j <= max_a; j += i)
        {
            cnt[j] = 0;
        }
    }
    int ans = 0;
    for (int i = 0; i < cnt.size(); i++)
    {
        assert(cnt[i] == 0 || cnt[i] == 1);
        ans += cnt[i];
    }
    cout << ans << endl;
}
