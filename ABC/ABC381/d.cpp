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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, int> now_num;
    int left = 0, right = 0;
    now_num[a[0]]++;
    int ans = 0;
    while (right < n) {
        bool flag = (left == right);
        while (right < n - 1 && (flag || !now_num.count(a[right])) && a[right + 1] == a[right]) {
            now_num[a[right]] += flag ? 1 : 2;
            right += 2;
            flag = false;
        }
        ans = max(ans, right - left);
        now_num[a[left]]--;
        if (now_num[a[left]] == 0) {
            now_num.erase(a[left]);
        }
        left++;
        if (left > right) {
            right = left;
            now_num[a[left]]++;
        }
    }
    REVERSE(a);
    now_num.clear();
    left = 0, right = 0;
    now_num[a[0]]++;
    while (right < n) {
        bool flag = (left == right);
        while (right < n - 1 && (flag || !now_num.count(a[right])) && a[right + 1] == a[right]) {
            now_num[a[right]] += flag ? 1 : 2;
            right += 2;
            flag = false;
        }
        ans = max(ans, right - left);
        now_num[a[left]]--;
        if (now_num[a[left]] == 0) {
            now_num.erase(a[left]);
        }
        left++;
        if (left > right) {
            right = left;
            now_num[a[left]]++;
        }
    }

    cout << ans << endl;
}
