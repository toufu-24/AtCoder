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

int32_t main(){
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++){
        cin >> h[i];
    }
    int now = 0;
    while(true){
        if(now == n-1){
            break;
        }
        if(h[now] < h[now + 1]){
            now++;
        }
        else{
            break;
        }
    }
    cout << h[now] << endl;
}
