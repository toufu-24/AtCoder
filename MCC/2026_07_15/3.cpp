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
    /*
    123456
    213456
    231456
    234156
    234516
    234561
    324561
    342561
    345261
    345621
    345612
    435612
    453612
    456312
    456132
    456123
    546123
    564123
    561423
    561243
    561234
    651234
    615234
    612534
    612354
    612345
    162345
    126345
    123645
    123465
    でループ
    */
    vector<int> ume = {
        123456,
        213456,
        231456,
        234156,
        234516,
        234561,
        324561,
        342561,
        345261,
        345621,
        345612,
        435612,
        453612,
        456312,
        456132,
        456123,
        546123,
        564123,
        561423,
        561243,
        561234,
        651234,
        615234,
        612534,
        612354,
        612345,
        162345,
        126345,
        123645,
        123465,
    };

    cout << ume[n % ume.size()] << endl;
}
