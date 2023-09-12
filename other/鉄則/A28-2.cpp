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
    modint::set_mod(10000);
    ll N;
    cin >> N;
    modint now = 0;
    for (int q = 0; q < N; q++)
    {
        char T;
        ll A;
        cin >> T >> A;
        switch (T)
        {
        case '+':
            now += A;
            break;
        case '-':
            now -= A;
            break;
        case '*':
            now *= A;
            break;
        }
        cout << now.val() << endl;
    }
}