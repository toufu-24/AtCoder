# #include <bits/stdc++.h>
# #include <atcoder/all>
# using namespace std;
# using namespace atcoder;

# #define all(v) v.begin(), v.end()
# #define sort(v) sort(v.begin(), v.end())
# #define reverse(v) reverse(v.begin(), v.end())
# #define ll int64_t
# #define ld long double

# ll A, B, N;
# ll f(ll x)
# {
#     return floor(A * x / B) - A * floor(x / B);
# }

# int main()
# {
#     cin >> A >> B >> N;
#     vector<int> ans;
#     ans.push_back(N);
#     if (B - 1 <= N)
#     {
#         ans.push_back(B - 1);
#     }
#     ll maximum = -1e9;
#     for (int i = 0; i < ans.size(); i++)
#     {
#         maximum = max(maximum, f(ans[i]));
#     }

#     cout << maximum << endl;
# }

#Pythonに変換
A, B, N = map(int, input().split())
ans = [N]
if B - 1 <= N:
    ans.append(B - 1)
maximum = -1e9
for i in range(len(ans)):
    maximum = max(maximum, ans[i] * A // B - A * (ans[i] // B))
print(maximum)
