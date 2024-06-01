#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        long long m,n,p;
        cin >> m >> n >> p;
        if(n == 0 && m == 0 && p == 0)return 0;
        vector<int> ans(m,0);
        ans[p-1] = 1;
        for(int i=0;i<n;i++){
            int x,y;
            cin >> x >> y;
            if(ans[x-1]+ans[y-1] == 1){
                ans[x-1] = 1;
                ans[y-1] = 1;
            }
        }
        int answer = 0;
        for(int i=0;i<m;i++)answer += ans[i];
        cout << answer << endl;
    }
    return 0;
}
