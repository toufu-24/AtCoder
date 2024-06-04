#include <bits/stdc++.h>
using namespace std;
#define ll long long 
ll mod = 1000000007;

int main()
{
    while (true)
    {
        ll n,m;
        cin >> n >> m;
        if(n == 0 && m == 0)return 0;
        vector<string> a(n);
        for(int i=0;i<n;i++)cin >> a[i];
        //dp[i][j][k]  k=0:(i,j)を選ばない場合の集合の数 k=1:(i,j)を選ぶ
        vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(m,vector<ll>(2,0)));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(a[i][j] == '.'){
                    dp[i][j][1] = 1;
                    if(i < 2)dp[i][j][0] = 1;
                }
            }
        }

        for(int i=2;i<n;i++){
            for(int j=0;j<m;j++){
                //i,jを選ばない
                if(j != 0){
                    dp[i][j][0] += dp[i-2][j-1][0] + dp[i-2][j-1][1];
                    dp[i][j][0] %= mod;
                }
                if(j != m-1){
                    dp[i][j][0] += dp[i-2][j+1][0] + dp[i-2][j+1][1];
                    dp[i][j][0] %= mod;
                }

                //i,jを選ぶ ->　i-2,j-1かi-2,j+1が選ばれてるとまずい
                if(j != 0 && a[i][j] == '.'){
                    if(a[i-2][j-1] == '.'){
                    dp[i][j][1] *= dp[i-2][j-1][0];
                    dp[i][j][1] %= mod;
                    }
                }
                if(j != m-1 && a[i][j] == '.'){
                    if(a[i-2][j+1] == '.'){
                    dp[i][j][1] *= dp[i-2][j+1][0];
                    dp[i][j][1] %= mod;
                    }
                }

                if(a[i][j] == '.' && dp[i][j][0] == 0 && dp[i][j][1] == 0){
                    dp[i][j][0] = 1,dp[i][j][1] = 1;
                }
            }   
        }
        ll ans = 1;
        for(int i=n-2;i<n;i++){
            for(int j = 0;j<m;j++){
            if(a[i][j] == '.')ans *= (dp[i][j][0]+dp[i][j][1]);
            ans %= mod;
            }
        }
        cout << ans << endl;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << dp[i][j][0] << "  ";
            }
            cout << endl;
        }
        cout << "=====================" << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << dp[i][j][1] << "  ";
            }
            cout << endl;
        }
    }
}
