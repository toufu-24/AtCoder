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

int32_t main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    auto sorted = a;
    SORT(sorted);

    int beg = 0;
    for (int i = 0; i <= n - k; i++) {
        if ((*cnt.begin()).first == a[i]) {
            cnt[a[i]]--;
            if (cnt[a[i]] == 0) {
                cnt.erase(a[i]);
            }
        } else {
            beg = i;
            break;
        }
    }

    sort(a.begin() + beg, a.begin() + beg + k);
    if(a == sorted){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
}
