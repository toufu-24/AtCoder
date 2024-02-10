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
    string N;
    cin >> N;
    sort(N);
    int ans = -1;
    do
    {
        // iとi+1で分割
        for (int i = 0; i < N.size() - 1; i++)
        {
            string left = N.substr(0, i + 1);
            string right = N.substr(i + 1);
            if (left[0] == '0' || right[0] == '0')
            {
                continue;
            }
            ans = max(ans, stoi(left) * stoi(right));
        }
    } while (next_permutation(all(N)));
    cout << ans;
}
