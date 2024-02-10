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
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    // a全部のxorと元全部のxorは同じ
    int xor_all = a[0];
    for (int i = 1; i < N; i++)
    {
        xor_all ^= a[i];
    }
    // vector<int> xor_bits;
    // // 2進数に変換
    // while (xor_all > 0)
    // {
    //     xor_bits.push_back(xor_all % 2);
    //     xor_all /= 2;
    // }

    // // 1 -> 奇数個 0 -> 偶数個

    vector<int> ans(N);
    for (int i = 0; i < N; i++)
    {
        ans[i] = xor_all ^ a[i];
        cout << ans[i] << "\n";
    }
}
