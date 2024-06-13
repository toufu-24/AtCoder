#include <bits/stdc++.h>
using namespace std;

int main(){
    while(true){
        long long n,m;
        cin >> n >> m;
        if(n == 0 && m == 0)return 0;
        vector<long long> a(n),w(m);
        for(int i=0;i<n;i++)cin >> a[i];
        for(int i=0;i<m;i++)cin >> w[i];
        long long pos = 1;
        for(int i=0;i<m;i++){
            pos *= 3;
        }
        vector<long long> three = {1,3,9,27,81,243,729,2187,6561,19683};
        set<long long> st;
        for(int i=0;i<pos;i++){
            long long tmp = 0;
            for(int j=0;j<m;j++){
                long long p = i/three[j];
                if(p%3 == 0)tmp -= w[j];
                if(p%3 == 2)tmp += w[j];
            }
            st.insert(tmp);
        }
        vector<long long> left;
        for(int i=0;i<n;i++){
            if(st.count(a[i]) == 0)left.push_back(a[i]);
        }
        long long ans = 1e18;
        long long x = st.size();
        if(left.size() == 0){
            cout << 0 << endl;
        }
        else{
            auto itr = st.begin();
            for(int i=0;i<x;i++){
                long long add = *itr;
                long long canditate = abs(left[0]-add);
                for(int j=1;j<left.size();j++){
                    long long up = left[j] + canditate, down = left[j] - canditate; 
                    if(st.count(up) == 0 && st.count(down) == 0){
                        canditate = 1e18;
                        break;
                    }
                }
                ans = min(ans,canditate);
                itr++;
            }
            if(ans == 1e18)ans = -1;
            cout << ans << endl;
        }
    }    
}